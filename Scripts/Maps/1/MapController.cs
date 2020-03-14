using Godot;

public class MapController : Node
{
	private Arwing arwing;
	private TextureRect aimCursor;

	public override void _Ready()
	{
		Input.SetMouseMode(Input.MouseMode.Captured);

		arwing		= GetNode<Arwing>("./Spatial/Arwing");
		aimCursor	= GetNode<TextureRect>("./UI/AimCursor");

		GD.Print(GetViewport().Size + " " + GetNode<Control>("./UI").RectSize);
	}

	public override void _Input(InputEvent @event)
	{
		if (@event is InputEventMouseMotion motion)
		{
			// TODO: Keep mouse within window
			aimCursor.RectPosition += motion.Relative;
		}
	}

	public override void _Process(float delta)
	{

	}
}
