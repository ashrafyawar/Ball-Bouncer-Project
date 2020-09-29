extends KinematicBody

var rotatevalueHorizontal = 0
var rotatevalueVertical = 0
var startPos = transform.origin   #veri kacirma durumu icin dusunuldu. transform.origin = startPos

# Called when the node enters the scene tree for the first time.
func _ready():
	pass 

func _physics_process(delta):
	#get_input()
	return

func get_input():
	if Input.is_action_pressed("yukari"):
		yukari()
	if Input.is_action_pressed("asagi"):
		asagi()
	if Input.is_action_pressed("sola"):
		sola()
	if Input.is_action_pressed("saga"):
		saga()
	if Input.is_action_pressed("ziplat"):
		ziplat()

func _move(rightArm, leftArm, upArm, downArm):
	if rightArm == 1 and leftArm == 1 and upArm == 1 and downArm == 1:
		ziplat()
	elif rightArm == -1 and leftArm == -1 and upArm == -1 and downArm == -1:
		indir()
	elif rightArm == 0 and leftArm == 0 and upArm == 0 and downArm == 0:
		return
	elif rightArm == 0 and upArm == -1:
		yukari()
	elif rightArm == 0 and upArm == 1:
		asagi()
	elif rightArm == 1 and upArm == 0:
		sola()
	elif rightArm == 1 and upArm == -1:
		sola()
		yukari()
	elif rightArm == 1 and upArm == 1:
		sola()
		asagi()
	elif rightArm == -1 and upArm == 0:
		saga()
	elif rightArm == -1 and upArm == 1:
		saga()
		asagi()
	elif rightArm == -1 and upArm == -1:
		saga()
		yukari()
		
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
		
func ziplat():  #tum bacaklar yukari
	transform.origin = Vector3(0,6,0)
	print("ziplatma")
	return
	
func indir():  #tum bacaklar asagi
	transform.origin = Vector3(0,5.2,0)
	print("indir")
	return

