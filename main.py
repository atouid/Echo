# provide the vector object to the python file
import shutil
from operator import itemgetter

from langchain.chat_models import ChatOpenAI
from langchain.embeddings import OpenAIEmbeddings
from langchain.prompts import ChatPromptTemplate, PromptTemplate
from langchain.schema.callbacks.streaming_stdout import StreamingStdOutCallbackHandler
from langchain.chains import ConversationalRetrievalChain
from langchain.memory import ConversationBufferMemory
import canvas
import pickle
import os


def run(question):
    openAIkey = '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'

    vectorstore = canvas.vector_db()
    course_name = canvas.course_name()

    course = ConversationBufferMemory(memory_key="chat_history", return_messages=True)

    finalPrompt = (f"Act like you are a tutor teaching an {course_name} at the University "
                   "of Michigan.")

    template = finalPrompt + """
        Chat History:
        {chat_history}
        Follow Up Input: {question}"""

    prompt = PromptTemplate(input_variables=["chat_history", "question"], template=template)

    # finalPromptFormatted = prompt.format(chat_history=course.chat_memory, question=input("What would you like to know?"))

    # Function to run the conversational chain
    def run_conversational_chain(question, chain, course):
        finalPromptFormatted = prompt.format(chat_history=course.chat_memory, question=question)
        d = {"question": finalPromptFormatted}
        response = chain.run(d)
        # Update the conversation history here
        course.chat_memory.add_message(question)
        course.chat_memory.add_message(response)
        return response

    # llm = ChatOpenAI(streaming=True, callbacks=[StreamingStdOutCallbackHandler()], temperature=0.65,  openai_api_key=openAIkey, model_name='gpt-4')
    #
    # chain = ConversationalRetrievalChain.from_llm(llm=llm, retriever=vectorstore.as_retriever(), memory=course)
    # d = {"question": finalPromptFormatted}
    # response = chain.run(d)

    # Initialize the conversational chain
    llm = ChatOpenAI(streaming=True, callbacks=[StreamingStdOutCallbackHandler()], temperature=0.65,
                     openai_api_key=openAIkey, model_name='gpt-4')
    chain = ConversationalRetrievalChain.from_llm(llm=llm, retriever=vectorstore.as_retriever(), memory=course)

    # Loop for continuous interaction
    while True:
        user_input = input("What would you like to know? ")
        if user_input.lower() in ['exit', 'quit', 'stop']:
            break
        response = run_conversational_chain(user_input, chain, course)
        print(response)

    # Serialize the chain object for persistence
    serialized_chain = pickle.dumps(chain)
    with open('chain.pkl', 'wb') as file:
        file.write(serialized_chain)

    # write the final prompt
    # implement pickle
    # front end send request then send the output
    # we won't know where the chain object is stored
    # each object has a byte representation just store it using pickle

    try:
        serialized_config = pickle.dumps(chain.config)
        with open('chain_config.pkl', 'wb') as file:
            file.write(serialized_config)
    except AttributeError:
        print("The chain object does not have a serializable 'config' attribute.")

    folder_path = "/Users/kassematoui/Desktop/flaskProject/pdf_files"
    # List all files in the directory
    for filename in os.listdir(folder_path):
        file_path = os.path.join(folder_path, filename)
        try:
            if os.path.isfile(file_path) or os.path.islink(file_path):
                os.unlink(file_path)  # Remove the file or link
            elif os.path.isdir(file_path):
                shutil.rmtree(file_path)  # Remove the directory (if you also want to remove directories)
        except Exception as e:
            print('Failed to delete %s. Reason: %s' % (file_path, e))
