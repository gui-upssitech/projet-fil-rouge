package dev.miniteldo.search.view;

// Project : graphical-interface

import dev.miniteldo.search.App;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.stage.Window;

import java.io.IOException;

/**
 * Classe Error ...
 * Date : 05/03/2022
 * Auteur : Julian
 */
public class Error {
    // Attributs
    private static Stage stage;


    /**
     * Generate pop up error with specified message. It's a modal popup
     *
     * @param owner        : current window
     * @param messageError : string message error
     */
    public static void popUpError(Window owner, String messageError) {
        String path = "/layout/" + "error.fxml";
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(App.class.getResource(path));
            Scene scene = new Scene(fxmlLoader.load());
            stage = new Stage();
            stage.setScene(scene);
            stage.initModality(Modality.WINDOW_MODAL);
            stage.initOwner(owner);
            stage.show();

        } catch (IOException e) {
            System.out.println("Err: failed to change the view");
            e.printStackTrace();
        }
    }
}
