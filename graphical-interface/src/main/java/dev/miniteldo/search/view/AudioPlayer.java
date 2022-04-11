package dev.miniteldo.search.view;

import javafx.event.Event;
import javafx.event.EventHandler;
import javafx.geometry.Pos;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.HBox;
import javafx.scene.media.Media;
import javafx.scene.media.MediaPlayer;
import javafx.util.Duration;

import java.io.File;

public class AudioPlayer extends HBox implements EventHandler<MouseEvent> {

    // Attributes
    private final Button button;

    private final MediaPlayer player;
    private final int timeCode;

    // Constructor
    public AudioPlayer(String filePath, int timeCode) {
        Media media = new Media(new File(filePath).toURI().toString());
        player = new MediaPlayer(media);
        this.timeCode = timeCode * 1000;

        this.setSpacing(12);
        this.setAlignment(Pos.CENTER);
        this.setId("audio-player");

        button = new Button("Play");
        button.setOnMouseClicked(this);

        this.getChildren().addAll(
                new Label("Time code: "+timeCode+"s"),
                button
        );
    }

    // Methods
    @Override
    public void handle(MouseEvent event) {
        if(player.getStatus() == MediaPlayer.Status.PLAYING) {
            player.pause();
            button.setText("Play");
        } else {
            player.seek(new Duration(timeCode));

            player.play();
            button.setText("Pause");
        }
    }

    public void stop() {
        player.stop();
    }

}