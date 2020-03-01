using Godot;

public class MenuController : Node
{
    private AnimationPlayer animation;
    private AudioStreamPlayer music;
    private AudioStreamPlayer effects;
    private Control ui;
    private Button start;
    private Button settings;
    private Button quit;

    public override void _Ready()
    {
        animation   = GetNode<AnimationPlayer>("./Animation");
        music       = GetNode<AudioStreamPlayer>("./Music");
        effects     = GetNode<AudioStreamPlayer>("./Effects");
        ui          = GetNode<Control>("./Control");
        start       = GetNode<Button>("./Control/Start");
        settings    = GetNode<Button>("./Control/Settings");
        quit        = GetNode<Button>("./Control/Quit");

        animation.Play("CameraIntroduction");
    }

    public override void _Process(float delta)
    {
        if (!animation.IsPlaying() && !ui.Visible)
        {
            // TODO: fadein UI
            System.Threading.Thread.Sleep(400);
            ui.Show();
        }

        // TODO: Loading manager
        // TODO: Settings logic
        // TODO: Confirmation on quit
        
        if (start.Pressed) GetTree().ChangeScene("res://Scenes/Maps/1.tscn");
        if (settings.Pressed) animation.Play("CameraMoveToSettings");
        if (quit.Pressed) GetTree().Quit();
    }
}
