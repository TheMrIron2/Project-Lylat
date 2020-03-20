using Godot;

public class MapController : Node
{
	private Arwing arwing;

	public override void _Ready()
	{
		Input.SetMouseMode(Input.MouseMode.Captured);

		arwing = GetNode<Arwing>("./Spatial/Arwing");
	}

	public override void _Process(float delta)
	{

	}
}
