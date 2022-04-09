package dev.miniteldo.search.model.engines.miniteldoengine.openedclosedmode;

import dev.miniteldo.search.model.engines.miniteldoengine.indexer.IndexerOptions;
import dev.miniteldo.search.model.tools.WatchFolder;

import java.io.IOException;

public class OpenedClosedMode {
    private static WatchFolder textWatchFolder;
    private static WatchFolder rgbImageWatchFolder;
    private static WatchFolder nbImageWatchFolder;
    private static WatchFolder audioWatchFolder;

    public static void init(String miniteldoEnginePath) throws IOException {
        textWatchFolder = new WatchFolder(miniteldoEnginePath, WatchFolderType.TEXT.getType(), IndexerOptions.TEXT);
        rgbImageWatchFolder = new WatchFolder(miniteldoEnginePath, WatchFolderType.RGB_IMAGE.getType(), IndexerOptions.IMAGE);
        nbImageWatchFolder = new WatchFolder(miniteldoEnginePath, WatchFolderType.NB_IMAGE.getType(), IndexerOptions.IMAGE);
        audioWatchFolder = new WatchFolder(miniteldoEnginePath, WatchFolderType.AUDIO.getType(), IndexerOptions.AUDIO);
    }

    public static void start() {
        textWatchFolder.start();
        rgbImageWatchFolder.start();
        nbImageWatchFolder.start();
        audioWatchFolder.start();
    }

    public static void stop() {
        textWatchFolder.end();
        rgbImageWatchFolder.end();
        nbImageWatchFolder.end();
        audioWatchFolder.end();
    }
}
