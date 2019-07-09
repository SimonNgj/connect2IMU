﻿//# define use_kalman

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO.Ports;
using Kalman;

public class mainCS : MonoBehaviour
{
    GameObject hand;
    GameObject index1, index2, index3;
    GameObject middle1, middle2, middle3;
    GameObject pinky0, pinky1, pinky2, pinky3;
    GameObject ring1, ring2, ring3;
    GameObject thumb1, thumb2, thumb3;
    SerialPort sp = new SerialPort("COM1", 9600, Parity.None, 8, StopBits.One);
    public float speed = 1f;

    #if (use_kalman)
    IKalmanWrapper kalman0, kalman1, kalman2, kalman3;
    #endif

    // Use this for initialization
    void Start ()
    {
        sp.Open();
        sp.ReadTimeout = 50;

        #if (use_kalman)
        // Using Kalman filter
        kalman0 = new MatrixKalmanWrapper();
        kalman1 = new MatrixKalmanWrapper();
        kalman2 = new MatrixKalmanWrapper();
        kalman3 = new MatrixKalmanWrapper();
        #endif

        //hand = GameObject.Find("LeftHand");
        //pinky0 = GameObject.Find("LeftHand/hands:l_hand_world/hands:b_l_hand/hands:b_l_pinky0");
        //pinky1 = GameObject.Find("LeftHand/hands:l_hand_world/hands:b_l_hand/hands:b_l_pinky0/hands:b_l_pinky1");
        //pinky2 = GameObject.Find("LeftHand/hands:l_hand_world/hands:b_l_hand/hands:b_l_pinky0/hands:b_l_pinky1/hands:b_l_pinky2");
        //pinky3 = GameObject.Find("LeftHand/hands:l_hand_world/hands:b_l_hand/hands:b_l_pinky0/hands:b_l_pinky1/hands:b_l_pinky2/hands:b_l_pinky3");

        index1 = GameObject.Find("l_hand_skeletal/hands:l_hand_world/hands:b_l_hand/hands:b_l_index1");
        index2 = GameObject.Find("l_hand_skeletal/hands:l_hand_world/hands:b_l_hand/hands:b_l_index1/hands:b_l_index2");
        index3 = GameObject.Find("l_hand_skeletal/hands:l_hand_world/hands:b_l_hand/hands:b_l_index1/hands:b_l_index2/hands:b_l_index3");

        thumb1 = GameObject.Find("l_hand_skeletal/hands:l_hand_world/hands:b_l_hand/hands:b_l_thumb1");
        thumb2 = GameObject.Find("l_hand_skeletal/hands:l_hand_world/hands:b_l_hand/hands:b_l_thumb1/hands:b_l_thumb2");
        thumb3 = GameObject.Find("l_hand_skeletal/hands:l_hand_world/hands:b_l_hand/hands:b_l_thumb1/hands:b_l_thumb2/hands:b_l_thumb3");

        middle1 = GameObject.Find("l_hand_skeletal/hands:l_hand_world/hands:b_l_hand/hands:b_l_middle1");
        middle2 = GameObject.Find("l_hand_skeletal/hands:l_hand_world/hands:b_l_hand/hands:b_l_middle1/hands:b_l_middle2");
        middle3 = GameObject.Find("l_hand_skeletal/hands:l_hand_world/hands:b_l_hand/hands:b_l_middle1/hands:b_l_middle2/hands:b_l_middle3");

        ring1 = GameObject.Find("l_hand_skeletal/hands:l_hand_world/hands:b_l_hand/hands:b_l_ring1");
        ring2 = GameObject.Find("l_hand_skeletal/hands:l_hand_world/hands:b_l_hand/hands:b_l_ring1/hands:b_l_ring2");
        ring3 = GameObject.Find("l_hand_skeletal/hands:l_hand_world/hands:b_l_hand/hands:b_l_ring1/hands:b_l_ring2/hands:b_l_ring3");
    }

    // Update is called once per frame
    void Update ()
    {
        if (sp.IsOpen)
        {
            try
            {
                string a = sp.ReadLine();
                string[] pos = a.Split(new char[] { ' ' });

                int rot0, rot1, rot2, rot3;
                int.TryParse(pos[0], out rot0);
                int.TryParse(pos[1], out rot1);
                int.TryParse(pos[2], out rot2);
                int.TryParse(pos[3], out rot3);

                #if (use_kalman)
                // Using Kalman filter
                Vector3 rot0a = new Vector3(0, 0, rot0);
                Vector3 rot1a = new Vector3(0, 0, rot1);
                Vector3 rot2a = new Vector3(0, 0, rot2);
                Vector3 rot3a = new Vector3(0, 0, rot3);

                Vector3 rot0b, rot1b, rot2b, rot3b;

                rot0b = kalman0.Update(rot0a);
                rot1b = kalman1.Update(rot1a);
                rot2b = kalman2.Update(rot2a);
                rot3b = kalman3.Update(rot3a);

                MoveObject((int)rot0b.z, (int)rot1b.z, (int)rot2b.z, (int)rot3b.z);
                #else
                // Raw data
                MoveObject(rot0, rot1, rot2, rot3);
                #endif
            }
            catch (System.Exception)
            {
            }
        }
    }

    void MoveObject(int obj0, int obj1, int obj2, int obj3)
    {
        thumb1.transform.localRotation = Quaternion.RotateTowards(thumb1.transform.localRotation, Quaternion.Euler(0, 160, 40 - 0.5f * obj0), 20f);
        thumb2.transform.localRotation = Quaternion.RotateTowards(thumb2.transform.localRotation, Quaternion.Euler(0, 0, 0 - 0.35f * obj0), 20f);
        thumb3.transform.localRotation = Quaternion.RotateTowards(thumb3.transform.localRotation, Quaternion.Euler(0, 0, 15 - 0.35f * obj0), 20f);

        index1.transform.localRotation = Quaternion.RotateTowards(index1.transform.localRotation, Quaternion.Euler(287f, 101f, 84 - obj1), 20f);
        index2.transform.localRotation = Quaternion.RotateTowards(index2.transform.localRotation, Quaternion.Euler(0, 0, 0 - 0.5f * obj1), 20f);
        index3.transform.localRotation = Quaternion.RotateTowards(index3.transform.localRotation, Quaternion.Euler(0, 0, 0 - 0.5f * obj1), 20f);

        middle1.transform.localRotation = Quaternion.RotateTowards(middle1.transform.localRotation, Quaternion.Euler(-80.4f, 18.7f, 165 - 0.7f * obj2), 20f);
        middle2.transform.localRotation = Quaternion.RotateTowards(middle2.transform.localRotation, Quaternion.Euler(0, 0, 0 - 0.6f * obj2), 20f);
        middle3.transform.localRotation = Quaternion.RotateTowards(middle3.transform.localRotation, Quaternion.Euler(0, 0, 0 - 0.6f * obj2), 20f);

        ring1.transform.localRotation = Quaternion.RotateTowards(ring1.transform.localRotation, Quaternion.Euler(-70f, -21.5f, -163 - 0.7f * obj3), 20f);
        ring2.transform.localRotation = Quaternion.RotateTowards(ring2.transform.localRotation, Quaternion.Euler(0, 0, 0 - 0.6f * obj3), 20f);
        ring3.transform.localRotation = Quaternion.RotateTowards(ring3.transform.localRotation, Quaternion.Euler(0, 0, 0 - 0.6f * obj3), 20f);
    }
}