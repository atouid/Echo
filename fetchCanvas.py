import requests
import json

AccessToken = "1770~ip9oqfEARU7ryIg3Z2AX7mE8XXDEPwo5Yi4sCVkkGsv3FE0RJ7FCdutwpp1b1Omg"
canvas_api_url = "https://umich.instructure.com/api/v1/"

headers = {
    "Authorization": f"Bearer {AccessToken}"
}

# Fetch courses
courses_url = canvas_api_url + "courses"
courses_response = requests.get(courses_url, headers=headers)

# Fetch To-Do items
todo_url = canvas_api_url + "users/self/todo"
todo_response = requests.get(todo_url, headers=headers)

if courses_response.status_code == 200 and todo_response.status_code == 200:
    courses = courses_response.json()
    todos = todo_response.json()

    # Structure data
    data = {
        "courses": [{ "name": course.get('name', 'Unknown Course Name'), "id": course.get('id', 'No ID') } for course in courses],
        "todos": [{ "title": item['assignment'].get('name', 'No Title'), "due_at": item['assignment'].get('due_at', 'No due date') }
                  for item in todos if 'assignment' in item]
    }

    # Write data to JSON file
    with open('canvas_data.json', 'w') as json_file:
        json.dump(data, json_file, indent=4)
else:
    print("Failed to retrieve data from Canvas.")
