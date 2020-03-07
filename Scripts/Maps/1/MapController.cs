using Godot;

public class MapController : Node
{
    private Arwing arwing;

    public override void _Ready()
    {
        arwing = GetNode<Arwing>("./Spatial/Arwing");
        arwing.UTurn();
    } 
}
