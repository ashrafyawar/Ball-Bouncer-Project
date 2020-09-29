extends InterpolatedCamera

onready var cameraImage = get_node("CameraImage")
var counter = 0
var start = false 
# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

func _physics_process(delta):
	get_input()
	
func change_stats():
	start=true
	
func get_input():

	if start and Input.is_action_just_released("changeCam"):
		counter = (counter +1 )%2
		if counter == 0:
			make_current()
		if counter ==1:
			cameraImage.make_current()
		
