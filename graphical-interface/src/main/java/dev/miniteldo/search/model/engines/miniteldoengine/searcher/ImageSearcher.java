package dev.miniteldo.search.model.engines.miniteldoengine.searcher;

import dev.miniteldo.search.model.engines.SearchResult;
import dev.miniteldo.search.model.engines.miniteldoengine.admin.Configurations;
import dev.miniteldo.search.model.engines.miniteldoengine.admin.Configurator;
import dev.miniteldo.search.model.engines.miniteldoengine.command.Command;
import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;

public class ImageSearcher extends Searcher {

    private String hexaCode;

    public ImageSearcher(String miniteldoEnginePath, SearcherType searcherType) {
        super();
        this.searcherType = searcherType;
        this.path = (searcherType == SearcherType.IMAGE_RGB_PATH) ? "data/image/RGB/" : "data/image/NB/";
        this.miniteldoEnginePath = miniteldoEnginePath;
    }

    public ImageSearcher(String miniteldoEnginePath, SearcherType searcherType, String hexacode) {
        super();
        this.searcherType = searcherType;
        this.path = "data/image/RGB/";
        this.miniteldoEnginePath = miniteldoEnginePath;
        this.hexaCode = hexacode;
    }

    @Override
    protected ArrayList<SearchResult> searchInner(String request) throws IOException {
        ArrayList<SearchResult> searchResults = new ArrayList<>();
        Command command = new Command(miniteldoEnginePath, searcherType, request);
        BufferedReader reader = command.getResult();
        String absolutePath = System.getProperty("user.dir").toString();
        String line;

        while((line = reader.readLine()) != null) {
            String[] splitResults = line.split(" ");

            SearchResult searchResult = new SearchResult(absolutePath.substring(0, absolutePath.lastIndexOf("/")+1) + path + splitResults[0], Float.parseFloat(splitResults[1]));
            searchResults.add(searchResult);
        }
        return searchResults;
    }

    public ArrayList<SearchResult> findByHexacode() {
        /* We want  an image of 200 x 200 pixels. This is equivalent to get a discrete sphere of 200 x 200 values volume in the euclidian space (0, R, G, B) */
        /* The search color is the center of the sphere. We can easily determinate the discrete radius of the sphere using this formula : */
        /* 4 . pi / 3 . r³ = 200² <=> r = 21 */

        HashMap<Configurations, Integer> configs = Configurator.loadConfigs(miniteldoEnginePath);
        Integer imageComparisonValue = configs.get(Configurations.IMAGE_THRESHOLD);

        try {
            Configurator.configure(miniteldoEnginePath, Configurations.IMAGE_THRESHOLD, "0.1");
        } catch (IOException e) {
            e.printStackTrace();
        }

        BufferedImage bufferedImage = new BufferedImage(200, 200, BufferedImage.TYPE_INT_RGB);
        int[] colors = new int[200 * 200];
        int[][][] matrix = new int[200][200][3];

        float r = 21;
        float d = 2 * r;
        int idx = 0;

        int Rref = Integer.decode("0x" + hexaCode.substring(0, 2));
        int Gref = Integer.decode("0x" + hexaCode.substring(2, 4));
        int Bref = Integer.decode("0x" + hexaCode.substring(4, 6));

        for(int i = 0; i < 256; i++) {
            for(int j = 0; j < 256; j++) {
                for(int k = 0; k < 256; k++) {
                    int value = ((i - Rref) * (i - Rref) + (j - Gref) * (j - Gref) + (k - Bref) * (k - Bref));
                    if(value <= d * d / 4.0) {
                        colors[idx] = (i << 16) + (j << 8) + k;
                        idx++;
                    }
                }
            }
        }

        for(int i = 0; i < 200; i++) {
            for(int j = 0; j < 200; j++) {
                int color = colors[(j + i * 200) % idx];
                matrix[i][j][0] = (color & 0xFF0000) >> 16;
                matrix[i][j][1] = (color & 0x00FF00) >> 8;
                matrix[i][j][2] = (color & 0x0000FF);
                bufferedImage.setRGB(i, j, color);
            }
        }

        /* matrix text file */
        try {
            FileWriter matrixFile = new FileWriter("../data/image/RGB/" + hexaCode + ".txt");
            matrixFile.write("200 200 3\n");
            for(int k = 0; k < 3; k++) {
                for(int i = 0; i < 200; i++) {
                    for (int j = 0; j < 200; j++) {
                        matrixFile.write(String.valueOf(matrix[i][j][k]) + " ");
                    }
                    matrixFile.write('\n');
                }
            }
            matrixFile.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        /* jpg image file */
        File jpgImage = new File("../data/image/RGB/" + hexaCode + ".jpg");
        try {
            ImageIO.write(bufferedImage, "jpg", jpgImage);
        } catch (IOException e) {
            e.printStackTrace();
        }

        ArrayList<SearchResult> results = new ArrayList<>();

        try {
             results = searchInner("../data/image/RGB/" + hexaCode + ".jpg");
        } catch (IOException e) {
            e.printStackTrace();
        }

        try {
            Configurator.configure(miniteldoEnginePath, Configurations.IMAGE_THRESHOLD, String.valueOf(imageComparisonValue));
        } catch (IOException e) {
            e.printStackTrace();
        }

        return results;
    }
}
