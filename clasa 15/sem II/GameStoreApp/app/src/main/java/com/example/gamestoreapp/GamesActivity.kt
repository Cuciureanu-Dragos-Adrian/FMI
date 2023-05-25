package com.example.gamestoreapp

import android.animation.ObjectAnimator
import android.app.NotificationChannel
import android.app.NotificationManager
import android.app.PendingIntent
import android.content.Context
import android.content.Intent
import android.content.pm.PackageManager
import android.graphics.Color
import android.net.Uri
import android.os.Build
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.ImageView
import android.widget.TextView
import android.widget.Toast
import androidx.annotation.RequiresApi
import androidx.core.app.ActivityCompat
import androidx.core.app.NotificationCompat
import androidx.core.app.NotificationManagerCompat
import androidx.core.content.ContextCompat
import com.bumptech.glide.Glide


class GamesActivity : AppCompatActivity() {

    private lateinit var shareButton: Button
    private lateinit var buyButton: Button

    private val channelId = "my_channel_id"
    private val notificationId = 101

    private lateinit var image: Uri
    private var title: String? = null
    private var description: String? = null
    private var price: String? = null

    @RequiresApi(Build.VERSION_CODES.TIRAMISU)
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_games)

        val imageGame: ImageView = findViewById(R.id.image)
        val titleGame: TextView = findViewById(R.id.title)
        val descriptionGame: TextView = findViewById(R.id.description)
        val priceGame: TextView = findViewById(R.id.price)

        val bundle: Bundle? = intent.extras
        if (bundle != null) {

            title = bundle.getString("title")
            description = bundle.getString("description")
            price = bundle.getString("price")
        }

        if (intent.hasExtra("image")) {
            image = intent.getParcelableExtra<Uri>("image")!!

            Glide.with(this)
                .load(image)
                .into(imageGame)
        }

        titleGame.text = title
        descriptionGame.text = "Description: $description"
        priceGame.text = "Price: $price"

        shareButton = findViewById<Button>(R.id.shareButton)

        shareButton.setOnClickListener {
            val intent = Intent(Intent.ACTION_SEND)
            intent.type = "text/plain"
            intent.putExtra(Intent.EXTRA_TEXT, description)

            val chooser = Intent.createChooser(intent, "Sharing text")
            startActivity(chooser)
        }

        buyButton = findViewById<Button>(R.id.buyButton)

        createNotificationChannel()

        buyButton.setOnClickListener {
            sendNotification()
        }

        val animator1 = ObjectAnimator.ofFloat(shareButton, "alpha", 0f, 1f)
        val animator2 = ObjectAnimator.ofFloat(buyButton, "alpha", 0f, 1f)

        animator1.duration = 2000
        animator2.duration = 2000

        animator1.start()
        animator2.start()
    }

    private fun createNotificationChannel() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            val channel = NotificationChannel(
                channelId,
                "Game bought successfully",
                NotificationManager.IMPORTANCE_DEFAULT
            ).apply {
                description = "You bought $title"
            }
            val notificationManager =
                getSystemService(Context.NOTIFICATION_SERVICE) as NotificationManager
            notificationManager.createNotificationChannel(channel)
        }
    }

    @RequiresApi(Build.VERSION_CODES.TIRAMISU)
    private fun sendNotification() {
        val intent = Intent(this, GamesActivity::class.java).apply {
            flags = Intent.FLAG_ACTIVITY_NEW_TASK or Intent.FLAG_ACTIVITY_CLEAR_TASK
            putExtra("image", image)
            putExtra("title", title)
            putExtra("description", description)
            putExtra("price", price)
        }

        val pendingIntent: PendingIntent = PendingIntent.getActivity(
            this,
            0,
            intent,
            PendingIntent.FLAG_MUTABLE or PendingIntent.FLAG_UPDATE_CURRENT
        )

        val builder = NotificationCompat.Builder(this, channelId)
            .setSmallIcon(R.drawable.baseline_videogame_asset_24)
            .setContentTitle("Game bought successfully")
            .setContentText("You bought $title")
            .setContentIntent(pendingIntent)
            .setPriority(NotificationCompat.PRIORITY_DEFAULT)

        if (ActivityCompat.checkSelfPermission(
                this,
                android.Manifest.permission.POST_NOTIFICATIONS
            ) == PackageManager.PERMISSION_GRANTED
        ) {
            with(NotificationManagerCompat.from(this)) {
                notify(notificationId, builder.build())
            }
        } else {
            ActivityCompat.requestPermissions(
                this,
                arrayOf(android.Manifest.permission.POST_NOTIFICATIONS),
                0
            )
        }
    }

    override fun onNewIntent(intent: Intent?) {
        super.onNewIntent(intent)

        val bundle = intent?.extras

        if(bundle != null) {
            title = bundle.getString("title")
            description = bundle.getString("description")
            price = bundle.getString("price")
        }

        if (intent?.hasExtra("image") == true) {
            image = intent.getParcelableExtra<Uri>("image")!!

        }
    }
}