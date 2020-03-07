using Godot;

public class Arwing : Spatial
{
    public enum ControlMode
    {
        FixedMovement,
        FullMovement
    }

    public enum VelocityMode
    {
        Constant,
        Controllable
    }

    private AnimationPlayer animation;
    private StaticBody body;
    private AudioStreamPlayer3D effects;

    public override void _Ready()
    {
        animation   = GetNode<AnimationPlayer>("./Animation");
        body        = GetNode<StaticBody>("./Body");
        effects     = GetNode<AudioStreamPlayer3D>("./Effects");
    }

    public override void _Process(float delta)
    {
        
    }
}
