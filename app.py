from flask import Flask, request, jsonify
from flask_cors import CORS
import json
from main import run

app = Flask(__name__)
CORS(app)


# Import the function from main.py
# from main import run_conversational_chain

# Root URL route
@app.route('/')
def home():
    return 'Welcome to the Flask App!'


@app.route('/get-canvas-data')
def get_canvas_data():
    with open('canvas_data.json') as json_file:
        data = json.load(json_file)
    return jsonify(data)


@app.route('/ask-tutor', methods=['POST'])
def ask_tutor():
    question = request.json.get('question')
    response = run(question)
    return jsonify({'response': response})


if __name__ == '__main__':
    app.run(debug=False)
