package com.example.gamestoreapp

import android.content.Intent
import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.TextView
import com.example.gamestoreapp.databinding.FragmentProfileBinding
import com.google.firebase.auth.FirebaseAuth

class ProfileFragment : Fragment() {

    private lateinit var binding: FragmentProfileBinding
    private lateinit var firebaseAuth: FirebaseAuth

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = FragmentProfileBinding.inflate(layoutInflater)
    }

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        firebaseAuth = FirebaseAuth.getInstance()

        val view = inflater.inflate(R.layout.fragment_profile, container, false)
        val email = firebaseAuth.currentUser?.email
        val logoutButton = view.findViewById<Button>(R.id.signOutButton)

        view.findViewById<TextView>(R.id.textView).text = "Logged in as: \n$email"

        logoutButton.setOnClickListener {
            firebaseAuth.signOut()

            val intent = Intent(activity, LogInActivity::class.java)
            activity?.startActivity(intent)
            activity?.finish()
        }

        return view
    }

}