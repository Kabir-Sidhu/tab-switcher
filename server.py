from flask import Flask, jsonify
import pyautogui

app = Flask(__name__)

@app.route('/switch')
def shock():
    print("Switched")
    pyautogui.hotkey("alt", "tab", interval=0.1)
    return jsonify({"switched": True})

if __name__ == '__main__':
    app.run(host="0.0.0.0")
