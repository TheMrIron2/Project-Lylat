using Godot;

public class ArwingController : Spatial
{
	public override void _Process(float delta) => GlobalTransform = new Transform(Transform.basis, new Vector3(Transform.origin.x, Transform.origin.y, Transform.origin.z - 0.01f));

	public override void _Input(InputEvent @event)
	{
		if (@event is InputEventKey eventKey)
		{
			switch (eventKey.Scancode)
			{
			case (int)KeyList.W:
				GlobalTransform = new Transform(Transform.basis, new Vector3(Transform.origin.x, Transform.origin.y + 0.5f, Transform.origin.z));
				break;

			case (int)KeyList.S:
				GlobalTransform = new Transform(Transform.basis, new Vector3(Transform.origin.x, Transform.origin.y - 0.5f, Transform.origin.z));
				break;
			};

			switch (eventKey.Scancode)
			{
			case (int)KeyList.A:
				GlobalTransform = new Transform(Transform.basis, new Vector3(Transform.origin.x - 0.5f, Transform.origin.y, Transform.origin.z));
				break;

			case (int)KeyList.D:
				GlobalTransform = new Transform(Transform.basis, new Vector3(Transform.origin.x + 0.5f, Transform.origin.y, Transform.origin.z));
				break;
			};
		}		
	}
}
