using Godot;

public class AnimationController : AnimationPlayer
{
	public override void _Ready()
	{
		Play("PlanetSpin");
	}
}
