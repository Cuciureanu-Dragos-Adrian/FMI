package com.example.gamestoreapp

import android.app.Activity.RESULT_OK
import android.app.ProgressDialog
import android.content.ActivityNotFoundException
import android.content.Intent
import android.graphics.Bitmap
import android.graphics.drawable.BitmapDrawable
import android.net.Uri
import android.os.Build
import android.os.Bundle
import android.os.Environment
import android.provider.MediaStore
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.EditText
import android.widget.ImageView
import android.widget.TextView
import android.widget.Toast
import androidx.annotation.RequiresApi
import androidx.core.content.FileProvider
import com.example.gamestoreapp.databinding.FragmentAddGameBinding
import com.example.gamestoreapp.databinding.FragmentProfileBinding
import com.google.android.material.textfield.TextInputEditText
import com.google.firebase.auth.FirebaseAuth
import com.google.firebase.database.DatabaseReference
import com.google.firebase.database.FirebaseDatabase
import com.google.firebase.storage.FirebaseStorage
import com.google.firebase.storage.StorageReference
import java.io.File
import java.io.FileOutputStream
import java.text.SimpleDateFormat
import java.time.LocalDate
import java.util.BitSet
import java.util.Date
import java.util.Locale

// TODO: Rename parameter arguments, choose names that match
// the fragment initialization parameters, e.g. ARG_ITEM_NUMBER
private const val ARG_PARAM1 = "param1"
private const val ARG_PARAM2 = "param2"

/**
 * A simple [Fragment] subclass.
 * Use the [AddGameFragment.newInstance] factory method to
 * create an instance of this fragment.
 */
class AddGameFragment : Fragment() {
    // TODO: Rename and change types of parameters
    private var param1: String? = null
    private var param2: String? = null

    private lateinit var binding: FragmentAddGameBinding
    private lateinit var firebaseAuth: FirebaseAuth
    private lateinit var databaseReference: DatabaseReference
    private lateinit var storageReference: StorageReference

    private lateinit var titleView: EditText
    private lateinit var priceView: EditText
    private lateinit var descriptionView: EditText

    private lateinit var title: String
    private lateinit var price: String
    private lateinit var description: String
    private lateinit var image: ImageView
    private lateinit var imageUri: Uri

    private val requestImageCapture = 100

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        arguments?.let {
            param1 = it.getString(ARG_PARAM1)
            param2 = it.getString(ARG_PARAM2)
        }

        binding = FragmentAddGameBinding.inflate(layoutInflater)
    }

    @RequiresApi(Build.VERSION_CODES.O)
    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        val view = inflater.inflate(R.layout.fragment_add_game, container, false)

        val formatter = SimpleDateFormat("yyyy_MM_dd_HH_mm_ss", Locale.getDefault())
        val now = Date()
        val fileName = formatter.format(now)

        firebaseAuth = FirebaseAuth.getInstance()
        databaseReference = FirebaseDatabase.getInstance().getReference("games/$fileName")
        storageReference = FirebaseStorage.getInstance().getReference("images/$fileName")

        // Inflate the layout for this fragment
        return view
    }

    companion object {
        /**
         * Use this factory method to create a new instance of
         * this fragment using the provided parameters.
         *
         * @param param1 Parameter 1.
         * @param param2 Parameter 2.
         * @return A new instance of fragment AddGame.
         */
        // TODO: Rename and change types and number of parameters
        @JvmStatic
        fun newInstance(param1: String, param2: String) =
            AddGameFragment().apply {
                arguments = Bundle().apply {
                    putString(ARG_PARAM1, param1)
                    putString(ARG_PARAM2, param2)
                }
            }
    }

    @RequiresApi(Build.VERSION_CODES.O)
    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        image = view.findViewById(R.id.image)

        val uid = firebaseAuth.currentUser?.uid

        val photoButton = view.findViewById<Button>(R.id.photoButton)
        val uploadButton = view.findViewById<Button>(R.id.uploadButton)

        photoButton.setOnClickListener {
            val intent = Intent()
            /*intent.action = MediaStore.ACTION_IMAGE_CAPTURE*/
            intent.type = "image/*"
            intent.action = Intent.ACTION_GET_CONTENT

            try {
                startActivityForResult(intent, requestImageCapture)
            } catch (e: ActivityNotFoundException) {
                Toast.makeText(activity, "Error + $e", Toast.LENGTH_SHORT).show()
            }
        }

        uploadButton.setOnClickListener {

            titleView = view.findViewById(R.id.title)
            priceView = view.findViewById(R.id.price)
            descriptionView = view.findViewById(R.id.description)

            title = titleView.text.toString()
            price = priceView.text.toString()
            description = descriptionView.text.toString()

            val game = Game(title, description, price)

            if (uid != null) {
                databaseReference.setValue(game).addOnCompleteListener {
                    if (it.isSuccessful) {
                        uploadImage()

                        Toast.makeText(activity, "Uploaded data", Toast.LENGTH_SHORT).show()
                    } else {
                        Toast.makeText(activity, "Failed to upload data", Toast.LENGTH_SHORT).show()
                    }
                }
            } else {
                Toast.makeText(activity, "UID empty", Toast.LENGTH_SHORT).show()
            }
        }
    }

    @Deprecated("Deprecated in Java")
    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {

        if (requestCode == requestImageCapture && resultCode == RESULT_OK) {
            imageUri = data?.data!!
            image.setImageURI(imageUri)
        } else {
            super.onActivityResult(requestCode, resultCode, data)

        }
    }

    private fun uploadImage() {
        val progressDialog = ProgressDialog(activity)
        progressDialog.setMessage("Uploading Image")
        progressDialog.setCancelable(false)
        progressDialog.show()

        storageReference.putFile(imageUri).addOnSuccessListener {
            binding.image.setImageURI(null)

            Toast.makeText(activity, "Uploaded image", Toast.LENGTH_SHORT).show()

            if (progressDialog.isShowing) {
                progressDialog.dismiss()
            }
        }.addOnFailureListener {
            Toast.makeText(activity, "Failed to upload image", Toast.LENGTH_SHORT).show()

            if (progressDialog.isShowing) {
                progressDialog.dismiss()
            }
        }
    }
}