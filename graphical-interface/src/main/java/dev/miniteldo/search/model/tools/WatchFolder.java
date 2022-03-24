package dev.miniteldo.search.model.tools;

import dev.miniteldo.search.model.engines.miniteldoengine.indexer.Indexer;
import dev.miniteldo.search.model.engines.miniteldoengine.indexer.IndexerMode;
import dev.miniteldo.search.model.engines.miniteldoengine.indexer.IndexerOptions;

import java.io.IOException;
import java.nio.file.*;

public class WatchFolder extends Thread {

    private final WatchKey watchKey;
    private final String miniteldoPath;
    private final IndexerOptions indexerOptions;
    private boolean stopped;

    public WatchFolder(String miniteldoPath, String path, IndexerOptions indexerOptions) throws IOException {
        this.miniteldoPath = miniteldoPath;
        this.indexerOptions = indexerOptions;
        WatchService watchService = FileSystems.getDefault().newWatchService();
        Path directory = Path.of("../data/" + path);
        watchKey = directory.register(watchService, StandardWatchEventKinds.ENTRY_CREATE);
    }

    public void run() {
        stopped = false;
        while (!stopped) {
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }


            for (WatchEvent<?> event : watchKey.pollEvents()) {
                WatchEvent<Path> pathEvent = (WatchEvent<Path>) event;
                Path fileName = pathEvent.context();
                WatchEvent.Kind<?> kind = event.kind();
                if (kind == StandardWatchEventKinds.ENTRY_CREATE) {
                    switch(indexerOptions) {
                        case TEXT:
                            try {
                                Indexer.indexText(miniteldoPath, IndexerMode.UPDATE);
                            } catch (IOException e) {
                                e.printStackTrace();
                            }
                            break;

                        case IMAGE:
                            try {
                                Indexer.indexImage(miniteldoPath, IndexerMode.UPDATE);
                            } catch (IOException e) {
                                e.printStackTrace();
                            }
                            break;

                        default:
                            try {
                                Indexer.indexAudio(miniteldoPath, IndexerMode.UPDATE);
                            } catch (IOException e) {
                                e.printStackTrace();
                            }
                            break;
                    }
                }
            }
        }
    }

    public void end() {
        stopped = true;
    }
}
