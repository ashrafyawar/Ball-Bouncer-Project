extends CanvasLayer

var port
var start = false
onready var ball = get_node("Ball")
onready var rightArm = get_node("rightArm")
onready var leftArm = get_node("leftArm")
onready var upArm = get_node("upArm")
onready var downArm = get_node("downArm")
onready var zemin = get_node("zemin")
onready var lineEdit = get_node("LineEdit")
onready var infoText = get_node("infoText")
onready var startButton = get_node("Button")
onready var camInfo = get_node("Camera1")
onready var portText = get_node("portText")

func _ready():
	$HTTPRequest.connect("request_completed", self, "_on_request_completed")

func runner(x,y,z,r,l,u,d):
	ball._move(x,y,z)
	zemin._move(r, l, u, d)
	rightArm._move(r)
	leftArm._move(l)
	upArm._move(u)
	downArm._move(d)

func _on_HTTPRequest_request_completed(result, response_code, headers, body):
	print("Result: " + str(result))
	
	if result != 0:  # not success
		portText.text="Not Connected"
		portText.visible=true
		return
	
	var body_str = body.get_string_from_utf8()
	
	var tokens = body_str.split(",", false)
	if tokens.size() == 7:
		
		var x_float = float(tokens[0])
		var z_float = float(tokens[1])
		var h_float = float(tokens[2])
		
		var max_x = 500.0
		var x_pos = x_float / max_x * 9.0
		x_pos -= 4.5
		
		var max_z = 500.0
		var z_pos = z_float / max_z * 9.0
		z_pos -= 4.5
		
		var max_h = 80.0
		print(str(h_float))
		var y_pos = (60 - h_float) / 7.0 + 6.5
		
		# don't go under ground 2
		if y_pos < 6.5:
			y_pos = 6.5
		
		ball._move(x_pos, y_pos, -z_pos)
		
		yield(get_tree().create_timer(0.1), "timeout")
		start = true
		tempRunner()
		$HTTPRequest.request(str(port))
	else:
		portText.text="Error: data parsing"
		portText.visible=true
	pass
	

func _connect_button_pressed():
	port = lineEdit.text
	if port== "":
		return 
	port = "http://" + port + "/simulation"
	print("Address : " + port)
	if $HTTPRequest.request(str(port)) == ERR_INVALID_PARAMETER:
		print("fail")
		portText.text="Not Connected"
		portText.visible=true
		return
	pass


func tempRunner():
	camInfo.change_stats()
	print(port)
	portText.text="Address: " + port
	portText.visible=true
	startButton.visible = false
	lineEdit.visible = false
	infoText.visible = true
