using Godot;

public class UIController : Control
{
	private Button start;
	private Button settings;
	private Button quit;

	public override void _Ready()
	{
		OS.WindowPosition = new Vector2(0, 0);

		start = GetNode<Button>("./ButtonStart");
		settings = GetNode<Button>("./ButtonSettings");
		quit = GetNode<Button>("./ButtonQuit");
	}

	public override void _Process(float delta)
	{
		if (start.Pressed) GetTree().ChangeScene("res://Scenes/Game.tscn");
		else if (settings.Pressed) GetTree().ChangeScene("res://Scenes/Settings.tscn");
		else if (quit.Pressed) GetTree().Quit();
	}
}
