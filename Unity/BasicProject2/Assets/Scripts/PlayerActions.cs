using UnityEngine;
using System.Collections;
using InControl;

public class PlayerActions : PlayerActionSet
{
    public PlayerAction Left;
    public PlayerAction Right;
    public PlayerAction Up;
    public PlayerAction Down;
    public PlayerOneAxisAction MoveHorz;
    public PlayerOneAxisAction MoveVert;

    public PlayerActions()
    {
        Left = CreatePlayerAction("MoveHorz Left");
        Right = CreatePlayerAction("MoveHorz Right");
        Up = CreatePlayerAction("MoveVert Up");
        Down = CreatePlayerAction("MoveVert Down");
        MoveHorz = CreateOneAxisPlayerAction(Left, Right);
        MoveVert = CreateOneAxisPlayerAction(Down, Up);
    }
}