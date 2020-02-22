using Godot;

public class ArwingController : Spatial
{
	public override void _Input(InputEvent @event)
	{
		if (@event is InputEventKey eventKey && eventKey.Pressed) switch (eventKey.Scancode)
		{
		// TODO: replace these with mapped keys in the button mapper from Godot
		case (int)KeyList.W:
			GlobalTransform = new Transform(Transform.basis, new Vector3(Transform.origin.x, Transform.origin.y, Transform.origin.z - 1.0f));
			break;

		case (int)KeyList.S:
			GlobalTransform = new Transform(Transform.basis, new Vector3(Transform.origin.x, Transform.origin.y, Transform.origin.z + 1.0f));
			break;
		
		case (int)KeyList.A:
			GlobalTransform = new Transform(Transform.basis, new Vector3(Transform.origin.x - 1.0f, Transform.origin.y, Transform.origin.z));
			break;
		
		case (int)KeyList.D:
			GlobalTransform = new Transform(Transform.basis, new Vector3(Transform.origin.x + 1.0f, Transform.origin.y, Transform.origin.z));
			break;
		};
		
	}
}
