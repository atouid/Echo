import pickle

from langchain.embeddings import OpenAIEmbeddings
from langchain.text_splitter import RecursiveCharacterTextSplitter
from langchain.vectorstores import Pinecone
from PyPDF2 import PdfReader
import requests
import pinecone
import pickle
import os

AccessToken = "1770~ip9oqfEARU7ryIg3Z2AX7mE8XXDEPwo5Yi4sCVkkGsv3FE0RJ7FCdutwpp1b1Omg"
canvas_api_url = "https://umich.instructure.com/api/v1/"
download_folder = "pdf_files"  # specify the folder where you want to download PDF files

# Set up the headers with the access token
headers = {
    "Authorization": f"Bearer {AccessToken}"
}

# Make the API request to get a list of courses for the user
courses_url = canvas_api_url + "courses"
courses_response = requests.get(courses_url, headers=headers)
course_name = ''

# Check if the request for courses was successful (status code 200)
if courses_response.status_code == 200:
    try:
        # Parse and work with the response data (in JSON format)
        courses = courses_response.json()

        # Filter out only active courses
        active_courses = [course for course in courses if course.get('workflow_state') == 'available']

        course_input = input("course_input:")
        # course_input = 'EECS 270 001 FA 2022'
        # Assuming you want to download files for all active courses
        for course in active_courses:
            course_id = course['id']
            files_url = canvas_api_url + f"courses/{course_id}/files"
            files_response = requests.get(files_url, headers=headers)
            if course_input == course['name']:
                course_name = course['name']
                # Check if the request for files was successful (status code 200)
                if files_response.status_code == 200:
                    # Parse and work with the response data (in JSON format)
                    files = files_response.json()

                    # Download PDF files
                    for file in files:
                        if file['filename'].endswith('.pdf'):
                            pdf_url = file['url']
                            pdf_response = requests.get(pdf_url, headers=headers)

                            # Create a folder if it doesn't exist
                            os.makedirs(download_folder, exist_ok=True)

                            # Save the PDF file
                            with open(os.path.join(download_folder, file['filename']), 'wb') as pdf_file:
                                pdf_file.write(pdf_response.content)

                                print(f"Downloaded PDF: {file['filename']} for Course ID: {course_id}")

                else:
                    # Print an error message if the request for files was not successful
                    print(f"Error getting files: {files_response.status_code} - {files_response.text}")
            else:
                break
    except Exception as e:
        print(f"Error parsing JSON response for courses: {e}")
else:
    # Print an error message if the request for courses was not successful
    print(f"Error getting courses: {courses_response.status_code} - {courses_response.text}")


def vector_db():
    pinecone.init(
        api_key='b91c7ed0-daef-479f-a8e5-b4c4f9704256',
        environment='gcp-starter'
    )
    # index = pinecone.Index('course')

    pdf_directory = "/Users/kassematoui/Desktop/flaskProject/pdf_files"

    text = ''

    text_splitter = RecursiveCharacterTextSplitter(chunk_size=1000, chunk_overlap=20)
    # content =  text_splitter.split_text(text)

    try:
        for filename in os.listdir(pdf_directory):
            if filename.endswith('.pdf'):
                pdf_path = os.path.join(pdf_directory, filename)
                with open(pdf_path, 'rb') as file:
                    pdf_reader = PdfReader(file)
                    num_pages = len(pdf_reader.pages)
                    for page_num in range(num_pages):
                        page = pdf_reader.pages[page_num]
                        text += page.extract_text()
                    # print(f"Text extracted from {filename}:\n{text}\n")

                    embedding = OpenAIEmbeddings(openai_api_key='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')
                    # Upload to Pinecone
                    content = text_splitter.split_text(text)
                    docsearch = Pinecone.from_texts([t for t in content], embedding, index_name='course')
                    # index.upsert(vectors=[(filename, embedding)])
                    print(f"Uploaded embedding for {filename}")
                    return docsearch
    except Exception as e:
        print(f"Error processing PDF files: {e}")


def course_name():
    return course_name
