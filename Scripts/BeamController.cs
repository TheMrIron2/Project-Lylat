using Godot;

public class BeamController : StaticBody
{
	public override void _Process(float delta)
	{
		GlobalTransform = new Transform(Transform.basis, new Vector3(Transform.origin.x, Transform.origin.y, Transform.origin.z - 0.7f));
		// TODO: Check for collision
	}
}
