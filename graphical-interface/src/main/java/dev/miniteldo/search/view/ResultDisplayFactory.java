package dev.miniteldo.search.view;

import dev.miniteldo.search.view.enums.Component;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;
import org.w3c.dom.Document;
import org.w3c.dom.NodeList;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.nio.charset.StandardCharsets;
import java.text.DateFormat;
import java.util.Date;
import java.util.List;

import javax.xml.parsers.*;

/**
 * class: ResultDisplayFactory
 * author: Guillaume Roussin
 * date: 22/03/2022
 */
public class ResultDisplayFactory {

    // Methods
    public static Node createPreview(String filePath) {
        String extension = filePath.substring(filePath.lastIndexOf(".") + 1);

        return switch(extension) {
            case "xml" -> createTextPreview(filePath);
            case "bmp", "jpg" -> createImagePreview(filePath);
            case "wav" -> createAudioPreview(filePath);
            default -> new Pane();
        };
    }

    private static Node createImagePreview(String filePath) {
        try {

            FileInputStream inputStream = new FileInputStream(filePath);
            Image image = new Image(inputStream);
            return new ImageView(image);

        } catch(FileNotFoundException ignored) {
            return new Label("Couldn't load \""+filePath+"\"");
        }
    }

    private static Node createAudioPreview(String filePath) {
        return new Pane();
    }

    private static Node createTextPreview(String filePath) {

        try {
            DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
            DocumentBuilder builder = factory.newDocumentBuilder();

            Document doc = builder.parse(new File(filePath));
            doc.getDocumentElement().normalize();

            String componentPath = "/layout/" + Component.TEXT_PREVIEW.getPath();
            FXMLLoader fxmlLoader = new FXMLLoader(ResultDisplayFactory.class.getResource(componentPath));
            VBox root = fxmlLoader.load();

            Label title = (Label) root.lookup("#title"),
                details = (Label) root.lookup("#details"),
                summary = (Label) root.lookup("#summary");

            VBox contentBox = (VBox) root.lookup("#contentBox");

            title.setText(getTagContent(doc, "titre"));
            summary.setText(getTagContent(doc, "resume"));

            String auteur = getTagContent(doc, "auteur");
            String detailText = getTagContent(doc, "date") + " - " + (auteur.equals("") ? "Auteur inconnu" : auteur);
            details.setText(detailText);

            NodeList phrases = doc.getElementsByTagName("phrase");
            for (int i = 0; i < phrases.getLength(); i++) {
                String phraseContent = toUTF8(phrases.item(i).getTextContent());
                Label phrase = new Label(phraseContent);
                phrase.setMaxWidth(Double.MAX_VALUE);
                phrase.setWrapText(true);

                contentBox.getChildren().add(phrase);
            }

            return root;
        } catch(Exception e) {
            e.printStackTrace();
            return new Label("Couldn't load \""+filePath+"\"");
        }
    }

    private static String getTagContent(Document doc, String tagName) {
        String value = doc.getElementsByTagName(tagName).item(0).getTextContent();
        return toUTF8(value);
    }

    private static String toUTF8(String input) {
        return new String(input.getBytes(StandardCharsets.ISO_8859_1), StandardCharsets.UTF_8);
    }

}