<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Personalized Tutor Dashboard</title>
    <style>
        body {
            color: #64485C; /* Dark Purple Text */
            background-color: #836778; /* Light Purple Background */
        }
        /* Header styles */
        header {
            background-color: #2E1114; /* Dark blue color */
            color: #ADADAD;
            display: flex;
            justify-content: space-between;
            align-items: center;
            padding: 10px 20px;
            border-radius: 8px; /* Rounded corners */
            margin-bottom: 20px; /* Gap between header and boxes */
        }
        .header-logo {
            font-size: 24px;
            font-weight: bold;
            letter-spacing: 2px;
        }
        .profile {
            position: relative;
            display: inline-block;
        }
        .profile img {
            width: 40px;
            height: 40px;
            border-radius: 50%;
            cursor: pointer;
        }
        .dropdown-menu {
            display: none;
            position: absolute;
            right: 0;
            background-color: #f9f9f9;
            min-width: 160px;
            box-shadow: 0px 8px 16px 0px rgba(0,0,0,0.2);
            z-index: 1;
        }
        .dropdown-menu a {
            color: black;
            padding: 12px 16px;
            text-decoration: none;
            display: block;
        }
        .dropdown-menu a:hover {
            background-color: #501B1D;
        }

        /* Dashboard layout */
        .dashboard {
            display: grid;
            grid-template-columns: repeat(2, 1fr);
            gap: 20px;
        }
        .my-classes, .calendar, .spotify-player {
            grid-column: 1;
        }
        .chat-tutors {
            grid-column: 2;
            grid-row: 1 / 3; /* Span across the first two rows */
        }
        .spotify-player iframe {
            width: 100%;
            height: 380px; /* Adjust height as needed */
            border: none;
            border-radius: 10px;
        }
        /* Card styles */
        .card {
            background-color: #ADADAD;
            border-radius: 10px;
            padding: 20px;
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
            margin-bottom: 20px;
        }
        .card-header {
            font-size: 20px;
            color: #2E1114;
            margin-bottom: 15px;
        }
        .card-content, .calendar-content {
            font-size: 16px;
            color: #666;
        }
        .tutor-buttons, .calendar-events {
            background-color: #64485C;
            display: flex;
            flex-direction: column;
            gap: 10px;
        }
        .tutor-button, .calendar-event {
            border: none;
            padding: 10px 20px;
            border-radius: 5px;
            cursor: pointer;
            color: white;
            width: 100%;
        }
        .tutor-button {
            background-color: #5fbae9;
        }
        .calendar-event {
            background-color: #ffcc00; /* Default color for calendar events */
        }
        .calendar-event.chemistry {
            background-color: #ff6666;
        }
        .calendar-event.physics {
            background-color: #66ccff;
        }
        .toggle-button {
            border: none;
            padding: 10px;
            border-radius: 5px;
            cursor: pointer;
            background-color:  #64485C;
            margin-top: 10px;
        }

        @media (max-width: 768px) {
            .dashboard {
                grid-template-columns: 1fr;
            }
            .my-classes, .calendar, .chat-tutors, .spotify-player {
                grid-column: auto;
            }
        }
       /* Additional styles for Pomodoro Timer */
.pomodoro-timer {
    display: flex;
    flex-direction: column;
    align-items: center;
    gap: 10px;
}
.timer-display {
    font-size: 24px;
    margin-bottom: 10px;
    color: #d9534f; /* Red color for timer display */
    font-weight: bold;
}
.pomodoro-timer button {
    background-color: #5cb85c; /* Green color for buttons */
    color: white;
    padding: 10px 15px;
    border: none;
    border-radius: 5px;
    cursor: pointer;
    transition: background-color 0.3s;
}
.pomodoro-timer button:disabled {
    background-color: #cccccc;
    cursor: not-allowed;
}
.pomodoro-timer button:hover:not(:disabled) {
    background-color: #4cae4c; /* Darker green on hover */
} */
    </style>
</head>
<body>

    <header>
        <div class="header-logo">ECHO</div>
        <div class="profile">
            <img src="path_to_your_profile_picture.jpg" alt="Profile" onclick="toggleDropdown()">
            <div class="dropdown-menu" id="dropdownMenu">
                <a href="#">Settings</a>
                <a href="#">Sign Out</a>
            </div>
        </div>
    </header>

    <div class="dashboard">
        <!-- My Classes card -->
        <div class="card my-classes">
            <div class="card-header">My Classes</div>
            <div class="card-content">
                <p>You have <strong>3</strong> classes today.</p>
                <button class="toggle-button" onclick="toggleDetails(this)">Show Details</button>
                <div class="details" style="display:none">
                    <p>Math - 10:00 AM</p>
                    <p>Chemistry - 1:00 PM</p>
                    <p>Physics - 3:00 PM</p>
                </div>
            </div>
        </div>

        <!-- Calendar card -->
        <div class="card calendar">
            <div class="card-header">Calendar</div>
            <div class="calendar-content">
                <div class="calendar-events">
                    <button class="calendar-event">Math Assignment - Sep 20</button>
                    <button class="calendar-event chemistry">Chemistry Lab - Sep 22</button>
                    <button class="calendar-event physics">Physics Project - Sep 25</button>
                    <!-- More events can be added here -->
                </div>
            </div>
        </div>

        <!-- Chat with Your Tutors card -->
        <div class="card chat-tutors">
            <div class="card-header">Chat with Your Tutors</div>
            <div class="card-content">
                <div class="tutor-buttons">
                    <button class="tutor-button" onclick="openTutorChat('Math')">Math Tutor</button>
                    <button class="tutor-button" onclick="openTutorChat('Chemistry')">Chemistry Tutor</button>
                    <button class="tutor-button" onclick="openTutorChat('Physics')">Physics Tutor</button>
                    <!-- More buttons can be added here -->
                </div>
            </div>
        </div>

       <!-- Spotify Mini Player card -->
        <div class="card spotify-player">
            <div class="card-header">Spotify Mini Player</div>
            <div class="card-content" id="spotify-player-content">
                <!-- Spotify iframe embed code -->
                <iframe
                    title="Spotify Embed: Recommendation Playlist"
                    src="https://open.spotify.com/embed/playlist/5butyIagISF7l7R0o8FDUM?utm_source=generator&theme=0"
                    width="100%"
                    height="380"
                    style="min-height: 360px;"
                    frameborder="0"
                    allow="autoplay; clipboard-write; encrypted-media; fullscreen; picture-in-picture"
                    loading="lazy">
                </iframe>
            </div>
        </div>
        <div class="card pomodoro-timer">
            <div class="card-header">Pomodoro Timer</div>
            <div class="card-content" id="pomodoro-timer-content">
                <div class="timer-display" id="timer-display">25:00</div>
                <button id="start-timer" onclick="startTimer()">Start</button>
                <button id="pause-timer" onclick="pauseTimer()" disabled>Pause</button>
                <button id="reset-timer" onclick="resetTimer()" disabled>Reset</button>
            </div>
        </div>
</div>

    <script>
        // JavaScript for interactive elements
        function toggleDropdown() {
            var dropdown = document.getElementById("dropdownMenu");
            dropdown.style.display = dropdown.style.display === 'block' ? 'none' : 'block';
        }

        window.onclick = function(event) {
            if (!event.target.matches('.profile img')) {
                var dropdowns = document.getElementsByClassName("dropdown-menu");
                for (var i = 0; i < dropdowns.length; i++) {
                    var openDropdown = dropdowns[i];
                    if (openDropdown.style.display === "block") {
                        openDropdown.style.display = "none";
                    }
                }
            }
        }

        function toggleDetails(button) {
            var details = button.nextElementSibling;
            if (details.style.display === 'none') {
                details.style.display = 'block';
                button.textContent = 'Hide Details';
            } else {
                details.style.display = 'none';
                button.textContent = 'Show Details';
            }
        }

        function openTutorChat(subject) {
            window.open('https://chat.openai.com/', '_blank');
        }
        let timer;
let isTimerRunning = false;
let timeRemaining = 25 * 60; // 25 minutes in seconds

function updateDisplay() {
    const minutes = Math.floor(timeRemaining / 60);
    const seconds = timeRemaining % 60;
    document.getElementById('timer-display').textContent = `${minutes}:${seconds < 10 ? '0' : ''}${seconds}`;
}

function startTimer() {
    if (!isTimerRunning) {
        isTimerRunning = true;
        document.getElementById('pause-timer').disabled = false;
        document.getElementById('reset-timer').disabled = false;
        timer = setInterval(() => {
            if (timeRemaining > 0) {
                timeRemaining--;
                updateDisplay();
            } else {
                resetTimer();
                alert('Pomodoro finished!');
            }
        }, 1000);
    }
}

function pauseTimer() {
    clearInterval(timer);
    isTimerRunning = false;
}

function resetTimer() {
    clearInterval(timer);
    timeRemaining = 25 * 60;
    isTimerRunning = false;
    updateDisplay();
    document.getElementById('pause-timer').disabled = true;
    document.getElementById('reset-timer').disabled = true;
}

document.addEventListener('DOMContentLoaded', updateDisplay);

    </script>

</body>
</html>
