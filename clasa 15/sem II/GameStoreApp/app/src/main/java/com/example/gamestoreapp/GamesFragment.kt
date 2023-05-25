package com.example.gamestoreapp

import android.content.Intent
import android.net.Uri
import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.appcompat.widget.SearchView
import android.widget.Toast
import kotlin.collections.mutableMapOf
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.example.gamestoreapp.databinding.FragmentProfileBinding
import com.google.firebase.database.DataSnapshot
import com.google.firebase.database.DatabaseError
import com.google.firebase.database.DatabaseReference
import com.google.firebase.database.FirebaseDatabase
import com.google.firebase.database.ValueEventListener
import com.google.firebase.storage.FirebaseStorage
import com.google.firebase.storage.StorageReference
import java.util.Locale

// TODO: Rename parameter arguments, choose names that match
// the fragment initialization parameters, e.g. ARG_ITEM_NUMBER
private const val ARG_PARAM1 = "param1"
private const val ARG_PARAM2 = "param2"

/**
 * A simple [Fragment] subclass.
 * Use the [GamesFragment.newInstance] factory method to
 * create an instance of this fragment.
 */
class GamesFragment : Fragment() {
    // TODO: Rename and change types of parameters
    private var param1: String? = null
    private var param2: String? = null

    private lateinit var binding: FragmentProfileBinding
    private lateinit var adapter: GamesAdapter
    private lateinit var recyclerView: RecyclerView
    private lateinit var gamesArrayList: ArrayList<GamesData>
    private lateinit var searchView: SearchView

    private lateinit var databaseReference: DatabaseReference
    private lateinit var storageReference: StorageReference

    private lateinit var imagesMap: MutableMap<String, Uri>
    private lateinit var titlesMap: MutableMap<String, String>
    private lateinit var pricesMap: MutableMap<String, String>
    private lateinit var descriptionsMap: MutableMap<String, String>

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = FragmentProfileBinding.inflate(layoutInflater)

        arguments?.let {
            param1 = it.getString(ARG_PARAM1)
            param2 = it.getString(ARG_PARAM2)
        }
    }

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        databaseReference = FirebaseDatabase.getInstance().reference.child("games")
        storageReference = FirebaseStorage.getInstance().reference.child("images")

        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.fragment_games, container, false)
    }

    companion object {
        /**
         * Use this factory method to create a new instance of
         * this fragment using the provided parameters.
         *
         * @param param1 Parameter 1.
         * @param param2 Parameter 2.
         * @return A new instance of fragment Games.
         */
        // TODO: Rename and change types and number of parameters
        @JvmStatic
        fun newInstance(param1: String, param2: String) =
            GamesFragment().apply {
                arguments = Bundle().apply {
                    putString(ARG_PARAM1, param1)
                    putString(ARG_PARAM2, param2)
                }
            }
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)
        dataInitialize()
    }

    private fun dataInitialize() {
        gamesArrayList = ArrayList()

        imagesMap = mutableMapOf()
        titlesMap = mutableMapOf()
        pricesMap = mutableMapOf()
        descriptionsMap = mutableMapOf()

        storageReference.listAll().addOnSuccessListener { listResult ->
            // Loop through the list of images and download each one
            for (imageRef in listResult.items) {
                imageRef.downloadUrl.addOnSuccessListener { uri ->
                    val key = imageRef.toString().takeLast(19)

                    imagesMap[key] = uri

                    if(imagesMap.keys.size == listResult.items.size) {
                        if(descriptionsMap.keys.size == imagesMap.keys.size){
                            populateRecycler()
                        }
                    }
                }.addOnFailureListener { exception ->
                    Toast.makeText(activity, "Error: $exception", Toast.LENGTH_SHORT).show()
                }
            }
        }.addOnFailureListener { exception ->
            Toast.makeText(activity, "Error: $exception", Toast.LENGTH_SHORT).show()
        }

        databaseReference.addValueEventListener(object : ValueEventListener {
            override fun onDataChange(dataSnapshot: DataSnapshot) {
                for (childSnapshot in dataSnapshot.children) {

                    val key = childSnapshot.key.toString()

                    val item = childSnapshot.value as HashMap<*, *>

                    titlesMap[key] = item["title"] as String
                    pricesMap[key] = item["price"] as String
                    descriptionsMap[key] = item["description"] as String

                    if(descriptionsMap.keys.size == dataSnapshot.childrenCount.toInt()){
                        if(descriptionsMap.keys.size == imagesMap.keys.size){
                            populateRecycler()
                        }
                    }
                }
            }

            override fun onCancelled(error: DatabaseError) {
                Toast.makeText(activity, "Error: $error", Toast.LENGTH_SHORT).show()
            }
        })
    }

    private fun populateRecycler(){
        for (key in imagesMap.keys) {
            val game = GamesData(titlesMap[key]!!, imagesMap[key]!!, descriptionsMap[key]!!, pricesMap[key]!!)
            gamesArrayList.add(game)
        }
        gamesArrayList.sortBy { it.title }


        afterDataInitialize()
    }

    private fun afterDataInitialize(){
        val layoutManager = LinearLayoutManager(context)

        recyclerView = requireView().findViewById(R.id.recyclerView)
        searchView = requireView().findViewById(R.id.searchView)

        recyclerView.layoutManager = layoutManager
        recyclerView.setHasFixedSize(true)
        adapter = GamesAdapter(requireContext() ,gamesArrayList)
        recyclerView.adapter = adapter

        searchView.setOnQueryTextListener(object : SearchView.OnQueryTextListener {
            override fun onQueryTextSubmit(query: String?): Boolean {
                return false
            }

            override fun onQueryTextChange(newText: String?): Boolean {
                filterList(newText)
                return true
            }

        })

        adapter.setOnItemClickListener(object : GamesAdapter.onItemClickListener {
            override fun onItemClick(position: Int) {
                val intent = Intent(activity, GamesActivity::class.java)

                intent.putExtra("image", gamesArrayList[position].image)
                intent.putExtra("title", gamesArrayList[position].title)
                intent.putExtra("description", gamesArrayList[position].description)
                intent.putExtra("price", gamesArrayList[position].price)

                startActivity(intent)
            }
        })
    }

    private fun filterList(query: String?) {

        if (query != null) {
            val filteredList = ArrayList<GamesData>()

            for (i in gamesArrayList) {
                if (i.title.lowercase(Locale.ROOT).contains(query)) {
                    filteredList.add(i)
                }
            }

            if (filteredList.isEmpty()) {
                Toast.makeText(activity, "No Data found", Toast.LENGTH_SHORT).show()
                adapter.setFilteredList(filteredList)
            } else {
                adapter.setFilteredList(filteredList)
            }
        }
    }
}
