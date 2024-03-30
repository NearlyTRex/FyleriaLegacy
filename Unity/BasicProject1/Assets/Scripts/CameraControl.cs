using UnityEngine;
using System.Collections;
using InControl;

public class CameraActions : PlayerActionSet
{
	public PlayerAction Left;
	public PlayerAction Right;
	public PlayerAction Up;
	public PlayerAction Down;
	public PlayerOneAxisAction MoveHorz;
	public PlayerOneAxisAction MoveVert;
	public PlayerAction SwitchMovement;
	
	public CameraActions()
	{
		Left = CreatePlayerAction( "MoveHorz Left" );
		Right = CreatePlayerAction( "MoveHorz Right" );
		Up = CreatePlayerAction( "MoveVert Up" );
		Down = CreatePlayerAction( "MoveVert Down" );
		MoveHorz = CreateOneAxisPlayerAction( Left, Right );
		MoveVert = CreateOneAxisPlayerAction ( Down, Up );
		SwitchMovement = CreatePlayerAction ("SwitchMovement");
	}
}

public class CameraControl : MonoBehaviour {

	// Movement speed for camera
	private float moveSpeed = 1f;

	// Tilemap to keep within bounds
	private GameObject tilemap;
	private Transform tilemapTransform;
	private MeshRenderer tilemapRenderer;

	// Camera data
	private Transform cameraTransform;
	private Vector3 camDeltaMovement;

	// Calculated camera info
	private float vertExtent;
	private float horzExtent;
	private float rightBound;
	private float leftBound;
	private float topBound;
	private float bottomBound;

	// Input
	private CameraActions cameraActions;

	// Movement
	private enum MovementMode
	{
		None = 0,
		Simple, 
		Translate,
		MoveTowards,
		Count
	};
	private MovementMode currentMovementMode = MovementMode.None;

	// Use this for initialization
	void Start()
	{
		// Bind available actions
		cameraActions = new CameraActions ();
		cameraActions.Left.AddDefaultBinding( Key.LeftArrow );
		cameraActions.Left.AddDefaultBinding( InputControlType.DPadLeft );
		cameraActions.Right.AddDefaultBinding( Key.RightArrow );
		cameraActions.Right.AddDefaultBinding( InputControlType.DPadRight );
		cameraActions.Up.AddDefaultBinding( Key.UpArrow );
		cameraActions.Up.AddDefaultBinding( InputControlType.DPadUp );
		cameraActions.Down.AddDefaultBinding( Key.DownArrow );
		cameraActions.Down.AddDefaultBinding( InputControlType.DPadDown );
		cameraActions.SwitchMovement.AddDefaultBinding( Key.Space );
		cameraActions.SwitchMovement.AddDefaultBinding( InputControlType.Action1 );

		// Get tilemap data
		tilemap = GameObject.FindWithTag("Map");
		tilemapRenderer = FindComponent.GetChildComponentByTag<MeshRenderer>(tilemap, "Ground");
		tilemapTransform = tilemap.transform;

		// Get camera data
		Camera mainCamera = Camera.main.GetComponent<Camera>();
		cameraTransform = mainCamera.transform;
		camDeltaMovement = new Vector3(0, 0, 0);

		// Get vertical and horizontal extents of the camera frustum
		vertExtent = mainCamera.orthographicSize;  
		horzExtent = vertExtent * (mainCamera.aspect);

		// Calculate camera boundaries
		leftBound = (float)(tilemapRenderer.bounds.min.x + horzExtent);
		rightBound = (float)(tilemapRenderer.bounds.max.x - horzExtent);
		bottomBound = (float)(tilemapRenderer.bounds.min.y + vertExtent);
		topBound = (float)(tilemapRenderer.bounds.max.y - vertExtent);

		SwitchMovement();

		// Start by clamping to make sure we start within boundaries
		ClampToBounds();
	}
	
	// Update is called once per frame
	void Update()
	{
		// Get movement delta
		camDeltaMovement.x = GetHorizontalMovement();
		camDeltaMovement.y = GetVerticalMovement();

		if (cameraActions.SwitchMovement.WasPressed)
		{
			SwitchMovement();
		}
		
		switch (currentMovementMode)
		{
		case MovementMode.Simple:
			MoveCameraBySimple();
			break;
		case MovementMode.Translate:
			MoveCameraByTranslate();
			break;
		case MovementMode.MoveTowards:
			MoveCameraByMoveTowards();
			break;
		}

		// Clamp to boundaries
		ClampToBounds();
	}

	void SwitchMovement()
	{
		currentMovementMode++;
		if (currentMovementMode >= MovementMode.Count) {
			currentMovementMode = MovementMode.None + 1;
		}
		print ("Movement is now " + currentMovementMode);
	}

	void MoveCameraBySimple()
	{
		cameraTransform.position += (camDeltaMovement * moveSpeed * Time.deltaTime);
	}

	void MoveCameraByTranslate()
	{
		cameraTransform.Translate(camDeltaMovement * moveSpeed * Time.deltaTime);
	}

	void MoveCameraByMoveTowards()
	{
		cameraTransform.position = Vector3.MoveTowards(cameraTransform.position, cameraTransform.position + camDeltaMovement, moveSpeed * Time.deltaTime);
	}

	float GetHorizontalMovement()
	{
		return cameraActions.MoveHorz.Value;
	}

	float GetVerticalMovement()
	{
		return cameraActions.MoveVert.Value;
	}

	// Make sure that the camera stays within bounds of the tilemap
	void ClampToBounds()
	{
		Vector3 pos = cameraTransform.position;
		pos.x = Mathf.Clamp(pos.x, leftBound, rightBound);
		pos.y = Mathf.Clamp(pos.y, bottomBound, topBound);
		cameraTransform.position = pos;
	}
}
