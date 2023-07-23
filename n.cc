    // ---------------------------------------
    // TILE 18
    // Tile 18, Edge 69
    tiles[18].placeAdjVerticesE(edgeEnum::BL, 
        vector<Vertex*>{tiles[18].getVertexAdr(vertexEnum::ML), tiles[18].getVertexAdr(vertexEnum::BL)});
    tiles[18].placeAdjEdgesE(edgeEnum::BL, 
        vector<Edge*>{tiles[18].getEdgeAdr(edgeEnum::TL), tiles[18].getEdgeAdr(edgeEnum::B), tiles[16].getEdgeAdr(edgeEnum::B)});

    // Tile 18, Edge 70
    tiles[18].placeAdjVerticesE(edgeEnum::BR, 
        vector<Vertex*>{tiles[18].getVertexAdr(vertexEnum::MR), tiles[18].getVertexAdr(vertexEnum::BR)});
    tiles[18].placeAdjEdgesE(edgeEnum::BR, 
        vector<Edge*>{tiles[18].getEdgeAdr(edgeEnum::TR), tiles[18].getEdgeAdr(edgeEnum::B), tiles[17].getEdgeAdr(edgeEnum::B)});

    // Tile 18, Vertex 52
    tiles[18].placeAdjVerticesV(vertexEnum::BL, 
        vector<Vertex*>{tiles[18].getVertexAdr(vertexEnum::ML), tiles[18].getVertexAdr(vertexEnum::BR)});
    tiles[18].placeAdjEdgesV(vertexEnum::BL, 
        vector<Edge*>{tiles[18].getEdgeAdr(edgeEnum::BL), tiles[18].getEdgeAdr(edgeEnum::B)});
    
    // Tile 18, Edge 71
    tiles[18].placeAdjVerticesE(edgeEnum::B, 
        vector<Vertex*>{tiles[18].getVertexAdr(vertexEnum::BL), tiles[18].getVertexAdr(vertexEnum::BR)});
    tiles[18].placeAdjEdgesE(edgeEnum::B, 
        vector<Edge*>{tiles[18].getEdgeAdr(edgeEnum::BL), tiles[18].getEdgeAdr(edgeEnum::BR)});

    // Tile 18, Vertex 53
    tiles[18].placeAdjVerticesV(vertexEnum::BR, 
        vector<Vertex*>{tiles[18].getVertexAdr(vertexEnum::MR), tiles[18].getVertexAdr(vertexEnum::BL)});
    tiles[18].placeAdjEdgesV(vertexEnum::BR, 
        vector<Edge*>{tiles[18].getEdgeAdr(edgeEnum::BR), tiles[18].getEdgeAdr(edgeEnum::B)});
