extends Spatial

var rotatevalueHorizontal = 0
var rotatevalueVertical = 0
# Called when the node enters the scene tree for the first time.
func _ready():
	pass 

func _physics_process(delta):
	#get_input()
	return

func get_input():
	if Input.is_action_pressed("yukari"):
		asagi()
	if Input.is_action_pressed("asagi"):
		yukari()
	if Input.is_action_pressed("sola"):
		#sola()
		return
	if Input.is_action_pressed("saga"):
		#saga()
		return
	if Input.is_action_pressed("ziplat"):
		ziplat()

func _move(value):
	if value == 0:
		return
	elif value == 1:
		yukari()
	elif value == -1:
		asagi()


func yukari():
	if rotatevalueVertical < 8:
		rotate_x(-0.01)
		rotatevalueVertical = rotatevalueVertical + 1
func asagi():
	if rotatevalueVertical > -8:
		rotate_x(0.01)
		rotatevalueVertical = rotatevalueVertical - 1
func sola():
	if rotatevalueHorizontal > -8:
		rotate_z(0.01)
		rotatevalueHorizontal = rotatevalueHorizontal - 1
func saga():
	if rotatevalueHorizontal < 8:
		rotate_z(-0.01)
		rotatevalueHorizontal = rotatevalueHorizontal + 1
func ziplat():
	return
