package dev.miniteldo.search.view;

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
            VBox root = new VBox();

            root.getChildren().addAll(List.of(
                    createXMLDescriptor(doc, "titre"),
                    createXMLDescriptor(doc, "auteur"),
                    createXMLDescriptor(doc, "date"),
                    createXMLDescriptor(doc, "resume")
            ));

            NodeList phrases = doc.getElementsByTagName("phrase");
            for (int i = 0; i < phrases.getLength(); i++) {
                String phrase = toUTF8(phrases.item(i).getTextContent());
                root.getChildren().add(new Label(phrase));
            }

            return root;
        } catch(Exception ignored) {
            return new Label("Couldn't load \""+filePath+"\"");
        }
    }

    private static Label createXMLDescriptor(Document doc, String tagName) {
        String value = doc.getElementsByTagName(tagName).item(0).getTextContent();
        return new Label(toUTF8(value));
    }

    private static String toUTF8(String input) {
        return new String(input.getBytes(StandardCharsets.ISO_8859_1), StandardCharsets.UTF_8);
    }

}