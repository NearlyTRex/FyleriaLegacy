using UnityEngine;
using System.Collections;
using InControl;

public class CameraMovement : MonoBehaviour
{
    // Tile map info
    public MeshRenderer m_TilemapRenderer;
    private Bounds m_TilemapBounds;

    // Camera info
    private Camera m_MainCamera;
    private Transform m_MainCameraTransform;

    // Player info
    private GameObject m_Player;
    private Transform m_PlayerTransform;

    // Calculated camera info
    private float m_fCameraVertExtent;
    private float m_fCameraHorzExtent;
    private float m_fCameraLeftBound;
    private float m_fCameraRightBound;
    private float m_fCameraBottomBound;
    private float m_fCameraTopBound;

    private float smooth = 5.0f;

    // Use this for initialization
    void Start ()
    {
        // Get player data
        m_Player = GameObject.FindWithTag("Player");
        m_PlayerTransform = m_Player.transform;

        // Get tilemap data
        m_TilemapBounds = m_TilemapRenderer.bounds;

        // Get camera data
        m_MainCamera = Camera.main;
        m_MainCameraTransform = m_MainCamera.transform;

        // Get vertical and horizontal extents of the camera frustum
        m_fCameraVertExtent = m_MainCamera.orthographicSize;
        m_fCameraHorzExtent = m_fCameraVertExtent * (m_MainCamera.aspect);

        // Calculate camera boundaries
        m_fCameraLeftBound = (float)(m_TilemapBounds.min.x + m_fCameraHorzExtent);
        m_fCameraRightBound = (float)(m_TilemapBounds.max.x - m_fCameraHorzExtent);
        m_fCameraBottomBound = (float)(m_TilemapBounds.min.y + m_fCameraVertExtent);
        m_fCameraTopBound = (float)(m_TilemapBounds.max.y - m_fCameraVertExtent);

        // Set initial position
        UpdateCameraPosition();
    }
	
	// Update is called once per frame
	void Update ()
    {
        UpdateCameraPosition();
    }

    void UpdateCameraPosition()
    {
        Vector3 newPos = Vector3.Lerp(m_MainCameraTransform.position, m_PlayerTransform.position, Time.deltaTime * smooth);
        m_MainCameraTransform.position = new Vector3(newPos.x, newPos.y, m_MainCameraTransform.position.z);
        ClampToBounds();
    }

    // Make sure that the camera stays within bounds of the tilemap
    void ClampToBounds()
    {
        Vector3 pos = m_MainCameraTransform.position;
        pos.x = Mathf.Clamp(pos.x, m_fCameraLeftBound, m_fCameraRightBound);
        pos.y = Mathf.Clamp(pos.y, m_fCameraBottomBound, m_fCameraTopBound);
        m_MainCameraTransform.position = pos;
    }
}
