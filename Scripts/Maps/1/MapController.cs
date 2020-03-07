using Godot;

public class MapController : Node
{
    private Arwing arwing;

    public override void _Ready()
    {
        arwing = GetNode<Arwing>("./Spatial/Arwing");
    }

    public override void _Process(float delta)
    {
        if (Input.IsKeyPressed((int)KeyList.U)) arwing.UTurn();
    }
}
