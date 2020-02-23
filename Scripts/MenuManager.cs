using Godot;

public class MenuManager : Node
{
	private Button start;
	private Button settings;
	private Button quit;
	private SettingsManager dialog;

	public override void _Ready()
	{
		start = GetNode<Button>("./UI/Start");
		settings = GetNode<Button>("./UI/Settings");
		quit = GetNode<Button>("./UI/Quit");
		dialog = GetNode<SettingsManager>("./UI/Dialog");
		GetNode<AnimationPlayer>("./Player").Play("CameraMovement");
	}

	public override void _Process(float delta)
	{
		if (start.Pressed) GetTree().ChangeScene("res://Scenes/Game.tscn");
		else if (settings.Pressed) dialog.Visible = true;
		else if (quit.Pressed) GetTree().Quit();
	}
}
