package engine;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;

public class Test{

    public static void main(String[] args) throws IOException {
        /* process builder */
        ProcessBuilder processBuilder = new ProcessBuilder("./bridge/comparison_image", "color", "data/image/RGB/01.jpg");
        processBuilder = processBuilder.directory(new File("../search-engine"));
        Process process = processBuilder.start();

        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        while((line = reader.readLine()) != null) {
            System.out.println(line);
        }

    }
}