using Godot;
using System;
using System.Threading;

public class InitialLoader : Control
{
    private TextureRect loading;
    private Label info;
    private PackedScene menu;
    private bool loadDone = false;
    private bool textDone = false;
    private bool alphaDecrease = false;
    private bool waitText = true;
    private float alphaCounter = 0.0f;
    private float timeCounter = 0.0f;

    public override void _Ready()
    {
        Input.SetMouseMode(Input.MouseMode.Hidden);

        loading = GetNode<TextureRect>("./Loading");
        info = GetNode<Label>("./Info");

        System.Threading.Thread thread = new System.Threading.Thread(new ThreadStart(loaderThread));
        thread.Start();
    }

    public override void _Process(float delta)
    {
        if (loadDone && textDone) GetTree().ChangeSceneTo(menu);

        if (loading.RectRotation == 360.0f) loading.RectRotation = 0.0f;
        loading.RectRotation = loading.RectRotation + 0.1f;

        if (alphaDecrease && waitText)
        {
            if (timeCounter >= 150.0f) waitText = false;
            timeCounter = timeCounter + 0.01f;
            return;
        }

        info.SelfModulate = new Color(info.SelfModulate.r, info.SelfModulate.g, info.SelfModulate.b, alphaCounter);
        if (!alphaDecrease) alphaCounter = alphaCounter + 0.001f;
        else alphaCounter = alphaCounter - 0.001f;

        if (alphaCounter >= 1.0f) alphaDecrease = true;
        else if (alphaCounter <= 0.0f && alphaDecrease) textDone = true;
    }

    private void loaderThread()
    {
        ResourceInteractiveLoader loader = ResourceLoader.LoadInteractive("res://Scenes/Menu.tscn");

        while (!loadDone)
        {
            Error error = loader.Poll();
            switch (error)
            {
            case Error.Ok:
                break;

            case Error.FileEof:
                menu = (PackedScene)loader.GetResource();
                loadDone = true;
                break;
            
            default:
                throw new Exception($"Loading the Menu scene failed with code \"{error.ToString()}\".");
            }
            
        }
    }
}
