package dev.miniteldo.search.model.engine;

public interface SearchEngine {

    // Indexation
    // ====================================================

    /**
     * Effectue une indexation de tous les fichiers textes
     * @return Retourne vraie si l'indexation a réussie
     */
    boolean indexText();

    /**
     * Effectue une indexation de toutes les images
     * @return Retourne vraie si l'indexation a réussie
     */
    boolean indexImage();

    /**
     * Effectue une indexation de tous les fichiers audio
     * @return Retourne vraie si l'indexation a réussie
     */
    boolean indexAudio();

    /**
     * Effectue une indexation de tous les fichiers
     * @return Retourne vraie si l'indexation a réussie
     */
    boolean indexAll();

    // Search
    // ====================================================

    /**
     * Effectue une recherche textuelle à base de mots clés
     * @param positiveKeywords Mots-clés à include dans la recherche
     * @param negativeKeywords Mots-clés à exclure de la recherche
     * @return Liste des fichiers correspondants, triés par ordre de confiance
     */
    SearchResult[] keywordSearch(String[] positiveKeywords, String[] negativeKeywords);

    /**
     * Effectue une recherche textuelle à partir d'un fichier XML
     * @param filePath Chemin vers le fichier texte
     * @return Liste des fichiers similaires, triés par ordre de confiance
     */
    SearchResult[] textFileSearch(String filePath);

    /**
     * Effectue une recherche d'images noir & blanc similaires
     * @param filePath Chemin vers l'image
     * @return Liste des images similaires, triés par ordre de confiance
     */
    SearchResult[] bwImageSearch(String filePath);

    /**
     * Effectue une recherche d'images couleurs similaires
     * @param filePath Chemin vers l'image
     * @return Liste des images similaires, triés par ordre de confiance
     */
    SearchResult[] rgbImageSearch(String filePath);

    /**
     * Effectue une recherche audio à partir d'un fichier WAV
     * @param filePath Chemin vers l'extrait audio
     * @return Liste d'audios contenant le son donné, triés par ordre de confiance
     */
    SearchResult[] audioSearch(String filePath);



    // Configuration
    // ====================================================

    /**
     * Effectue l'authentification d'un administrateur
     * @param password Mot de passe de l'application
     * @return Retourne vrai si le mot de passe est correct
     */
    boolean login(String password);

    /**
     * Déconnecte l'utilisateur de la console admin
     * @return Confirmation de déconnexion
     */
    boolean logout();

    /**
     * Modifie le mot de passe administrateur
     * @param newPassword Nouveau mot de passe
     * @return Confirmation de changement de mot de passe
     */
    boolean changePassword(String newPassword);

    // TODO: Complete config functions
}
