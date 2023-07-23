    // ---------------------------------------
    // TILE 5
    // Tile 5, Vertex 5
    tiles[5].placeAdjVerticesV(vertexEnum::TL, 
        vector<Vertex*>{tiles[5].getVertexAdr(vertexEnum::TR), tiles[5].getVertexAdr(vertexEnum::ML)});
    tiles[5].placeAdjEdgesV(vertexEnum::TL, 
        vector<Edge*>{tiles[5].getEdgeAdr(edgeEnum::T), tiles[5].getEdgeAdr(edgeEnum::TL)});

    // Tile 5, Edge 5
    tiles[5].placeAdjVerticesE(edgeEnum::T,
        vector<Vertex*>{tiles[5].getVertexAdr(vertexEnum::TL), tiles[5].getVertexAdr(vertexEnum::TR)});
    tiles[5].placeAdjEdgesE(edgeEnum::T,
        vector<Edge*>{tiles[5].getEdgeAdr(edgeEnum::TL), tiles[5].getEdgeAdr(edgeEnum::TR)});

    // Tile 5, Vertex 1
    tiles[5].placeAdjVerticesV(vertexEnum::TR, 
        vector<Vertex*>{tiles[5].getVertexAdr(vertexEnum::TL), tiles[5].getVertexAdr(vertexEnum::MR)});
    tiles[5].placeAdjEdgesV(vertexEnum::TR, 
        vector<Edge*>{tiles[5].getEdgeAdr(edgeEnum::T), tiles[5].getEdgeAdr(edgeEnum::TR)});

    // Tile 5, Edge 1
    tiles[5].placeAdjVerticesE(edgeEnum::TL,
        vector<Vertex*>{tiles[5].getVertexAdr(vertexEnum::TL), tiles[5].getVertexAdr(vertexEnum::ML)});
    tiles[5].placeAdjEdgesE(edgeEnum::TL,
        vector<Edge*>{tiles[1].getEdgeAdr(edgeEnum::T), tiles[5].getEdgeAdr(edgeEnum::BL), tiles[5].getEdgeAdr(edgeEnum::T)});

    // Tile 5, Edge 2
    tiles[5].placeAdjVerticesE(edgeEnum::TR, 
        vector<Vertex*>{tiles[5].getVertexAdr(vertexEnum::TR), tiles[5].getVertexAdr(vertexEnum::MR)});
    tiles[5].placeAdjEdgesE(edgeEnum::TR, 
        vector<Edge*>{tiles[5].getEdgeAdr(edgeEnum::T), tiles[5].getEdgeAdr(edgeEnum::B), tiles[2].getEdgeAdr(edgeEnum::T)});

    // Tile 5, Vertex 3
    tiles[5].placeAdjVerticesV(vertexEnum::ML, 
        vector<Vertex*>{tiles[5].getVertexAdr(vertexEnum::TL), tiles[5].getVertexAdr(vertexEnum::BL), tiles[1].getVertexAdr(vertexEnum::TL)});
    tiles[5].placeAdjEdgesV(vertexEnum::ML, 
        vector<Edge*>{tiles[5].getEdgeAdr(edgeEnum::TL), tiles[5].getEdgeAdr(edgeEnum::BL), tiles[1].getEdgeAdr(edgeEnum::T)});

    // Tile 5, Vertex 4
    tiles[5].placeAdjVerticesV(vertexEnum::MR, 
        vector<Vertex*>{tiles[5].getVertexAdr(vertexEnum::TR), tiles[5].getVertexAdr(vertexEnum::BR), tiles[2].getVertexAdr(vertexEnum::TR)});
    tiles[5].placeAdjEdgesV(vertexEnum::MR, 
        vector<Edge*>{tiles[5].getEdgeAdr(edgeEnum::TR), tiles[5].getEdgeAdr(edgeEnum::BR), tiles[2].getEdgeAdr(edgeEnum::T)});

    // Tile 5, Edge 6
    tiles[5].placeAdjVerticesE(edgeEnum::BL, 
        vector<Vertex*>{tiles[5].getVertexAdr(vertexEnum::ML), tiles[5].getVertexAdr(vertexEnum::BL)});
    tiles[5].placeAdjEdgesE(edgeEnum::BL, 
        vector<Edge*>{tiles[5].getEdgeAdr(edgeEnum::TL), tiles[5].getEdgeAdr(edgeEnum::BL), tiles[1].getEdgeAdr(edgeEnum::T), tiles[1].getEdgeAdr(edgeEnum::BR)});

    // Tile 5, Edge 7
    tiles[5].placeAdjVerticesE(edgeEnum::BR, 
        vector<Vertex*>{tiles[5].getVertexAdr(vertexEnum::MR), tiles[5].getVertexAdr(vertexEnum::BR)});
    tiles[5].placeAdjEdgesE(edgeEnum::BR, 
        vector<Edge*>{tiles[5].getEdgeAdr(edgeEnum::TR), tiles[5].getEdgeAdr(edgeEnum::B), tiles[2].getEdgeAdr(edgeEnum::T), tiles[2].getEdgeAdr(edgeEnum::BL)});

    // Tile 5, Vertex 8
    tiles[5].placeAdjVerticesV(vertexEnum::BL, 
        vector<Vertex*>{tiles[5].getVertexAdr(vertexEnum::ML), tiles[5].getVertexAdr(vertexEnum::BR), tiles[1].getVertexAdr(vertexEnum::BR)});
    tiles[5].placeAdjEdgesV(vertexEnum::BL, 
        vector<Edge*>{tiles[5].getEdgeAdr(edgeEnum::BL), tiles[5].getEdgeAdr(edgeEnum::B), tiles[1].getEdgeAdr(edgeEnum::BR)});
    
    // Tile 5, Edge 15
    tiles[5].placeAdjVerticesE(edgeEnum::B, 
        vector<Vertex*>{tiles[5].getVertexAdr(vertexEnum::BL), tiles[5].getVertexAdr(vertexEnum::BR)});
    tiles[5].placeAdjEdgesE(edgeEnum::B, 
        vector<Edge*>{tiles[5].getEdgeAdr(edgeEnum::BL), tiles[5].getEdgeAdr(edgeEnum::BR), tiles[4].getEdgeAdr(edgeEnum::TL), tiles[4].getEdgeAdr(edgeEnum::TR)});

    // Tile 5, Vertex 9
    tiles[5].placeAdjVerticesV(vertexEnum::BR, 
        vector<Vertex*>{tiles[5].getVertexAdr(vertexEnum::MR), tiles[5].getVertexAdr(vertexEnum::BL), tiles[2].getVertexAdr(vertexEnum::BL)});
    tiles[5].placeAdjEdgesV(vertexEnum::BR, 
        vector<Edge*>{tiles[5].getEdgeAdr(edgeEnum::BR), tiles[5].getEdgeAdr(edgeEnum::B), tiles[2].getEdgeAdr(edgeEnum::BL)});

