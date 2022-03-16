package dev.miniteldo.search.model.engines.dummyengine;

import dev.miniteldo.search.model.engines.miniteldoengine.searcher.Searcher;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.SearcherFactory;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.SearcherType;

import java.util.ArrayList;
import java.util.Random;

/**
 * class: DummyEngine
 * author: Guillaume Roussin & Julian Trani
 * date: 14/03/2022
 */
public class DummyEngine implements SearchEngine {
    // Attributes
    private Searcher searcher;
    private ArrayList<SearchResult> searchResults;
    private final int MIN = 5;
    private final int MAX = 15;
    private final ArrayList<String> pathDataText = new ArrayList<String>();
    private final ArrayList<String> pathDataAudio = new ArrayList<String>();
    private final ArrayList<String> pathDataImageNB = new ArrayList<>();
    private final ArrayList<String> pathDataImageRGB = new ArrayList<>();

    // Constructor
    public DummyEngine() {
        this.searchResults = new ArrayList<>();

        //Init all datas
        initPathText();
        initPathAudio();
        initPathImageNB();
        initPathImageRGB();
    }

    // DO NOT OPEN => THIS IS TRASH
    public void initPathText() {
        this.pathDataText.add("03-Mimer_un_signal_nerveux_pour_utf8.xml");
        this.pathDataText.add("05-Edition___les_mots_et_utf8.xml");
        this.pathDataText.add("05-Le_Colombien_Juan_Pablo_Montoya_utf8.xml");
        this.pathDataText.add("05-Photographie___Philip_Blenkinsop_a_utf8.xml");
        this.pathDataText.add("05-Rock___l_Illinois_magique_de_utf8.xml");
        this.pathDataText.add("06-US_Open___Mauresmo_et_utf8.xml");
        this.pathDataText.add("08-Carlos_do_Carmo____Le_utf8.xml");
        this.pathDataText.add("08-La_mission_Deep_Impact_permet_utf8.xml");
        this.pathDataText.add("09-Miracle___le_cricket_est_utf8.xml");
        this.pathDataText.add("10-Le_cyclone_Katrina_complique_le_utf8.xml");
        this.pathDataText.add("12-Agassi_plie_face_au_meilleur_utf8.xml");
        this.pathDataText.add("12-Jean-Marie_Sevestre,_libraire_et_PDG_utf8.xml");
        this.pathDataText.add("12-Musique_classique___un__Oberon__utf8.xml");
        this.pathDataText.add("12-Musiques_du_monde___les_utf8.xml");
        this.pathDataText.add("13-Ligue_des_champions____Si_utf8.xml");
        this.pathDataText.add("14-Grippe_aviaire___l_OMS_exhorte_utf8.xml");
        this.pathDataText.add("15-Capturer_et_emprisonner_le_CO2,_utf8.xml");
        this.pathDataText.add("15-Capturer_et_emprisonner_le_CO_utf8.xml");
        this.pathDataText.add("15-La_mort_de_Robert_Wise,_utf8.xml");
        this.pathDataText.add("15-Lille_s_incline_dans_les_utf8.xml");
        this.pathDataText.add("15-Un_quasar_solitaire_bouleverse_les_utf8.xml");
        this.pathDataText.add("15-_Si_on_veut_aller_trop_utf8.xml");
        this.pathDataText.add("16-Une_sonde_japonaise_va_tenter_utf8.xml");
        this.pathDataText.add("18-Ligue_1___Lyon_a_utf8.xml");
        this.pathDataText.add("22-Danse___quarante_jeunes_de_utf8.xml");
        this.pathDataText.add("22-Des_laboureurs,_des_OGM..._et_utf8.xml");
        this.pathDataText.add("22-Grippe_aviaire___la_course_utf8.xml");
        this.pathDataText.add("22-Les_clubs_de_football_anglais_utf8.xml");
        this.pathDataText.add("23-Les_Bleus,_tombeurs_de_la_utf8.xml");
        this.pathDataText.add("26-Lyon_prend_ses_aises_en_utf8.xml");
        this.pathDataText.add("27-A_Lens,_le_Louvre_sera_utf8.xml");
        this.pathDataText.add("27-Le_Stade_de_France_s_ouvre_utf8.xml");
        this.pathDataText.add("28-A_Hossegor,_Kelly_Slater_peut_utf8.xml");
        this.pathDataText.add("28-Danse___Robyn_Orlin_et_utf8.xml");
        this.pathDataText.add("29-Ligue_des_champions___Lyon_utf8.xml");
    }

    public void initPathAudio() {
        this.pathDataAudio.add("corpus_fi.bin");
        this.pathDataAudio.add("corpus_fi.wav");
        this.pathDataAudio.add("jingle_fi.txt");
        this.pathDataAudio.add("corpus_fi.txt");
        this.pathDataAudio.add("jingle_fi.bin");
        this.pathDataAudio.add("jingle_fi.wav");
    }

    public void initPathImageNB() {
        this.pathDataImageNB.add("51.bmp");
        this.pathDataImageNB.add("52.bmp");
        this.pathDataImageNB.add("53.bmp");
        this.pathDataImageNB.add("54.bmp");
        this.pathDataImageNB.add("55.bmp");
        this.pathDataImageNB.add("56.bmp");
        this.pathDataImageNB.add("57.bmp");
        this.pathDataImageNB.add("58.bmp");
        this.pathDataImageNB.add("59.bmp");
        this.pathDataImageNB.add("60.bmp");
        this.pathDataImageNB.add("61.bmp");
        this.pathDataImageNB.add("62.bmp");
        this.pathDataImageNB.add("63.bmp");
    }

    public void initPathImageRGB() {
        this.pathDataImageRGB.add("01.jpg");
        this.pathDataImageRGB.add("02.jpg");
        this.pathDataImageRGB.add("03.jpg");
        this.pathDataImageRGB.add("04.jpg");
        this.pathDataImageRGB.add("05.jpg");
        this.pathDataImageRGB.add("06.jpg");
        this.pathDataImageRGB.add("07.jpg");
        this.pathDataImageRGB.add("08.jpg");
        this.pathDataImageRGB.add("09.jpg");
        this.pathDataImageRGB.add("10.jpg");
        this.pathDataImageRGB.add("11.jpg");
        this.pathDataImageRGB.add("12.jpg");
        this.pathDataImageRGB.add("13.jpg");
        this.pathDataImageRGB.add("14.jpg");
        this.pathDataImageRGB.add("15.jpg");
        this.pathDataImageRGB.add("16.jpg");
        this.pathDataImageRGB.add("17.jpg");
        this.pathDataImageRGB.add("18.jpg");
        this.pathDataImageRGB.add("19.jpg");
        this.pathDataImageRGB.add("20.jpg");
        this.pathDataImageRGB.add("21.jpg");
        this.pathDataImageRGB.add("22.jpg");
        this.pathDataImageRGB.add("23.jpg");
        this.pathDataImageRGB.add("24.jpg");
        this.pathDataImageRGB.add("25.jpg");
        this.pathDataImageRGB.add("26.jpg");
        this.pathDataImageRGB.add("27.jpg");
        this.pathDataImageRGB.add("28.jpg");
        this.pathDataImageRGB.add("29.jpg");
        this.pathDataImageRGB.add("30.jpg");
        this.pathDataImageRGB.add("31.jpg");
        this.pathDataImageRGB.add("32.jpg");
        this.pathDataImageRGB.add("33.jpg");
        this.pathDataImageRGB.add("34.jpg");
        this.pathDataImageRGB.add("35.jpg");
        this.pathDataImageRGB.add("36.jpg");
        this.pathDataImageRGB.add("37.jpg");
        this.pathDataImageRGB.add("38.jpg");
        this.pathDataImageRGB.add("39.jpg");
        this.pathDataImageRGB.add("40.jpg");
        this.pathDataImageRGB.add("41.jpg");
        this.pathDataImageRGB.add("42.jpg");
        this.pathDataImageRGB.add("43.jpg");
        this.pathDataImageRGB.add("44.jpg");
        this.pathDataImageRGB.add("45.jpg");
        this.pathDataImageRGB.add("46.jpg");
        this.pathDataImageRGB.add("47.jpg");
        this.pathDataImageRGB.add("48.jpg");
        this.pathDataImageRGB.add("49.jpg");
        this.pathDataImageRGB.add("50.jpg");
    }
    // Methods

    @Override
    public boolean indexText() {
        return true;
    }

    @Override
    public boolean indexImage() {
        return true;
    }

    @Override
    public boolean indexAudio() {
        return true;
    }

    @Override
    public boolean indexAll() {
        return true;
    }

    @Override
    public ArrayList<SearchResult> keywordSearch(String[] positiveKeywords, String[] negativeKeywords) {
        this.searcher = SearcherFactory.getSearcher(SearcherType.TEXT_KEYWORD);
        generateSearchResult(SearcherType.TEXT_KEYWORD);
        /*
            Minus set with positiveKeywords and negativeKeywords
        //        return searcher.search() // REAL CODE
         */
        return this.searchResults;
    }

    @Override
    public ArrayList<SearchResult> textFileSearch(String filePath) {
        this.searcher = SearcherFactory.getSearcher(SearcherType.TEXT_PATH);
        generateSearchResult(SearcherType.TEXT_PATH);
        return this.searchResults;
    }

    @Override
    public ArrayList<SearchResult> bwImageSearch(String filePath) {
        this.searcher = SearcherFactory.getSearcher(SearcherType.IMAGE_NB_PATH);
        generateSearchResult(SearcherType.IMAGE_NB_PATH);
        return this.searchResults;
    }

    @Override
    public ArrayList<SearchResult> rgbImageSearch(String filePath) {
        this.searcher = SearcherFactory.getSearcher(SearcherType.IMAGE_RGB_PATH);
        generateSearchResult(SearcherType.IMAGE_RGB_PATH);
        return this.searchResults;
    }

    @Override
    public ArrayList<SearchResult> audioSearch(String filePath) {
        this.searcher = SearcherFactory.getSearcher(SearcherType.AUDIO_PATH);
        generateSearchResult(SearcherType.AUDIO_PATH);
        return this.searchResults;
    }

    @Override
    public boolean login(String password) {
        return false;
    }

    @Override
    public boolean logout() {
        return false;
    }

    @Override
    public boolean changePassword(String newPassword) {
        return false;
    }

    @Override
    public boolean setConfig(Config configName, int value) {
        return false;
    }

    /**
     * Generate random value
     *
     * @return
     */
    public boolean generateSearchResult(SearcherType type) {
        // Variables
        int nombreAleatoire = this.MIN + (int) (Math.random() * ((this.MAX - this.MIN) + 1));
        int dataIndex;
        Random rand = new Random();
        float confidence;

        // clean arraylist
        this.searchResults.clear();

        // Generate value
        for (int i = 0; i < nombreAleatoire; i++) {
            confidence = rand.nextFloat() * (100) + 0;

            switch (type) {
                case TEXT_PATH:
                case TEXT_KEYWORD:
                    dataIndex = (int) (Math.random() * ((this.pathDataText.size() - 1) + 1));
                    this.searchResults.add(new SearchResult(this.pathDataText.get(dataIndex), confidence));
                    break;
                case IMAGE_RGB_PATH:
                    dataIndex = (int) (Math.random() * ((this.pathDataImageRGB.size() - 1) + 1));
                    this.searchResults.add(new SearchResult(this.pathDataImageRGB.get(dataIndex), confidence));
                case IMAGE_NB_PATH:
                    dataIndex = (int) (Math.random() * ((this.pathDataImageNB.size() - 1) + 1));
                    this.searchResults.add(new SearchResult(this.pathDataImageNB.get(dataIndex), confidence));
                    break;
                default:
                    dataIndex = (int) (Math.random() * ((this.pathDataAudio.size() - 1) + 1));
                    this.searchResults.add(new SearchResult(this.pathDataAudio.get(dataIndex), confidence));
                    break;
            }
        }
        return true;
    }

    @Override
    public String toString() {
        return "DummyEngine{" + "searchResults=" + searchResults + '}';
    }

    public static void main(String[] args) {
        DummyEngine dummyEngine = new DummyEngine();
        String FAKE_PATH = "a_path";
//        ArrayList<SearchResult> resultArrayList = dummyEngine.audioSearch(FAKE_PATH);
        ArrayList<SearchResult> resultArrayList = dummyEngine.textFileSearch(FAKE_PATH);
//        ArrayList<SearchResult> resultArrayList = dummyEngine.bwImageSearch(FAKE_PATH);
        for (SearchResult result : resultArrayList) {
            System.out.println(result);
        }
    }
}