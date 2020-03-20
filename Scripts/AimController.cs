using Godot;

public class AimController : Control
{
	[Export]
	public Color Normal		= new Color(44, 168, 229, 255);

	[Export]
	public Color Friendly	= new Color(44, 229, 51, 255);

	[Export]
	public Color Enemy		= new Color(239, 33, 33, 255);

	private TextureRect texture;
	private AnimationPlayer animation;

	public override void _Ready()
	{
		texture		= GetNode<TextureRect>("./Texture");
		animation	= GetNode<AnimationPlayer>("./Animation");

		texture.SelfModulate = Normal;
	}

	public override void _Input(InputEvent @event)
	{
		if (@event is InputEventMouseMotion motion)
		{
			// TODO: Keep mouse within window
			RectPosition += motion.Relative;
		}
	}

	public override void _Process(float delta)
	{
		// TODO: use raycasts or similar to find enemies and friendlies and change color / animation appropriately
	}
}