package com.example.gamestoreapp

import android.content.Context
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import android.widget.ImageView
import androidx.recyclerview.widget.RecyclerView
import com.bumptech.glide.Glide

class GamesAdapter(val context : Context, private var gamesList : List<GamesData>) : RecyclerView.Adapter<GamesAdapter.MyViewHolder>() {

    private lateinit var mListener : onItemClickListener

    interface onItemClickListener{
        fun onItemClick(position: Int)
    }

    fun setOnItemClickListener(listener : onItemClickListener){
        mListener = listener
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): MyViewHolder {
        val itemView = LayoutInflater.from(parent.context).inflate(R.layout.list_item, parent, false)
        return MyViewHolder(itemView, mListener)
    }

    fun setFilteredList(gamesList: ArrayList<GamesData>){
        this.gamesList = gamesList
        notifyDataSetChanged()
    }

    override fun getItemCount(): Int {
        return gamesList.size
    }

    override fun onBindViewHolder(holder: MyViewHolder, position: Int) {
        val currentItem = gamesList[position]
        holder.image.setImageURI(currentItem.image)
        holder.title.text = currentItem.title

        Glide.with(context)
            .load(currentItem.image)
            .into(holder.image)
    }

    class MyViewHolder(itemView : View, listener : onItemClickListener) : RecyclerView.ViewHolder(itemView){
        val image : ImageView = itemView.findViewById(R.id.image)
        val title : TextView = itemView.findViewById(R.id.title)

        init {
            itemView.setOnClickListener{
                listener.onItemClick(adapterPosition)
            }
        }
    }
}
