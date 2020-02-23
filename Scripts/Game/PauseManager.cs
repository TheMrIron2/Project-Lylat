using Godot;
using System;

public class PauseManager : Node
{
	private Label ammoLabel;
	private PopupDialog pauseScreen;
	private Button resumeButton;
	private Button settingsButton;
	private Button quitButton;
	private ConfirmationDialog dialog;

	public override void _Ready()
	{
		ammoLabel = GetNode<Label>("./UI/LabelAmmoSpeed");
		pauseScreen = GetNode<PopupDialog>("./UI/Popup");
		resumeButton = GetNode<Button>("./UI/Popup/Resume");
		quitButton = GetNode<Button>("./UI/Popup/Quit");
		dialog = GetNode<ConfirmationDialog>("./UI/Popup/Confirmation");
	}

	public override void _Input(InputEvent @event)
	{
		if (@event is InputEventKey eventKey && eventKey.Pressed && eventKey.Scancode == (int)KeyList.Escape)
		{
			GetTree().Paused = true;
			ammoLabel.Visible = false;
			pauseScreen.Visible = true;
		}
	}

	public override void _Process(float delta)
	{
		if (resumeButton.Pressed)
		{
			GetTree().Paused = false;
			ammoLabel.Visible = true;
			pauseScreen.Visible = false;
		}

		if (quitButton.Pressed)
		{
			dialog.Popup_();
		}
	}

	private void _on_Confirmation_confirmed()
	{
		GetTree().Paused = false;
		GetTree().ChangeScene("res://Scenes/Menu.tscn");
	}
}
