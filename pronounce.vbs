Set d =CreateObject("SAPI.SpVoice")
x = InputBox("Speak What?")
while NOT (x = "exit")
d.speak x
x = InputBox("Speak What? (Type exit to exit)")
wend