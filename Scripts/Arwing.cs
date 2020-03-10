using Godot;

public class Arwing : Spatial
{
    [Export]
    public float Acceleration = 0.1f;

    [Export]
    public float BoostAcceleration = 1.0f;

    [Export]
    public float BreakAcceleration = 0.01f;

    [Export]
    public float RailSwapSpeed = 0.09f;

    [Export]
    public float RailSwapLimit = 50.0f;

    private AnimationPlayer animation;
    private ArwingBody body;
    private AudioStreamPlayer3D effects;

    private bool fullMovement;
    private bool menuMode;

    public override void _Ready()
    {
        animation       = GetNode<AnimationPlayer>("./Animation");
        body            = GetNode<ArwingBody>("./Body");
        effects         = GetNode<AudioStreamPlayer3D>("./Effects");
        fullMovement    = false;
        menuMode        = false;
    }

    public override void _Process(float delta)
    {
        if (menuMode) return;

        if (Input.IsActionPressed(KeyMap.Boost)) GlobalTranslate(new Vector3(0, 0, BoostAcceleration));
        else if (Input.IsActionPressed(KeyMap.Break)) GlobalTranslate(new Vector3(0, 0, BreakAcceleration));
        else GlobalTranslate(new Vector3(0, 0, Acceleration));

        if (Input.IsActionPressed(KeyMap.Left) && !(GlobalTransform.origin.x > RailSwapLimit)) GlobalTranslate(new Vector3(RailSwapSpeed, 0, 0));
        else if (Input.IsActionPressed(KeyMap.Right) && !(GlobalTransform.origin.x < -RailSwapLimit)) GlobalTranslate(new Vector3(-RailSwapSpeed, 0, 0));

        if (Input.IsKeyPressed((int)KeyList.R)) GetTree().ReloadCurrentScene();
    }

    public void FullMovement(bool enable) => fullMovement = enable;
    public void MenuMode(bool enable) => menuMode = enable;
}
