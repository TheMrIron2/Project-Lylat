using Godot;

public class ButtonManager : Control
{
	private Button back;

	public override void _Ready()
	{
		back = GetNode<Button>("./ButtonBack");
	}

	public override void _Process(float delta)
	{
		if (back.Pressed) GetTree().ChangeScene("res://Scenes/Menu.tscn");
	}
}
