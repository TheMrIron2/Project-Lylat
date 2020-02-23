using Godot;

public class PauseManager : Node
{
	private Label ammoLabel;
	private PopupDialog pauseScreen;
	private Button resumeButton;
	private Button settingsButton;
	private Button quitButton;
	private ConfirmationDialog dialog;
	private SettingsManager settings;

	public override void _Ready()
	{
		ammoLabel = GetNode<Label>("./UI/LabelAmmoSpeed");
		pauseScreen = GetNode<PopupDialog>("./UI/Popup");
		resumeButton = GetNode<Button>("./UI/Popup/Resume");
		settingsButton = GetNode<Button>("./UI/Popup/Settings");
		quitButton = GetNode<Button>("./UI/Popup/Quit");
		dialog = GetNode<ConfirmationDialog>("./UI/Popup/Confirmation");
		settings = GetNode<SettingsManager>("./UI/Settings");
	}

	public override void _Input(InputEvent @event)
	{
		if (@event is InputEventKey eventKey && eventKey.Pressed && eventKey.Scancode == (int)KeyList.Escape)
		{
			GetTree().Paused = !GetTree().Paused;
			ammoLabel.Visible = !ammoLabel.Visible;
			pauseScreen.Visible = !pauseScreen.Visible;

			if (pauseScreen.Visible) Input.SetMouseMode(Input.MouseMode.Visible);
			else Input.SetMouseMode(Input.MouseMode.Captured);
		}
	}

	public override void _Process(float delta)
	{
		if (resumeButton.Pressed)
		{
			GetTree().Paused = false;
			ammoLabel.Visible = true;
			pauseScreen.Visible = false;
			Input.SetMouseMode(Input.MouseMode.Captured);
		}

		if (quitButton.Pressed)
		{
			dialog.Popup_();
		}

		if (settingsButton.Pressed) settings.Visible = true;
	}

	private void _on_Confirmation_confirmed()
	{
		GetTree().Paused = false;
		GetTree().ChangeScene("res://Scenes/Menu.tscn");
	}
}
