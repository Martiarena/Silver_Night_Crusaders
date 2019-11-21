void main()
{// Update script for displaying current HP from player 1 with colored bar
// Also displays current MP with numbers & displays current subweapon
    void P1 = getplayerproperty(0, "entity");
    void P2 = getplayerproperty(1, "entity");
    /*void Bar = getglobalvar("Bar");*/
    void WAx = getglobalvar("WAx");
    void WBib = getglobalvar("WBib");
    void WBom = getglobalvar("WBom");
    void WCrs = getglobalvar("WCrs");
    void WHoly = getglobalvar("WHoly");
    void WKnif = getglobalvar("WKnif");
    void WBmb = getglobalvar("WBmb");

    if(openborvariant("in_level")==1){
        if(P1){
            int HP1 = getentityproperty(P1, "health");
            int MP1 = getentityproperty(P1, "mp");
            int SubW = getglobalvar("00");

            if(MP1>=100){
                MP1 = 99;
            }

            drawstring(-99,-99,4, MP1);

        	if(SubW==1){
                drawsprite(WKnif, 13, 27, 11000);
        	} else if(SubW==2){
                drawsprite(WAx, 13, 27, 11000);
        	} else if(SubW==3){
                drawsprite(WCrs, 13, 26, 11000);
        	} else if(SubW==4){
                drawsprite(WHoly, 13, 26, 11000);
        	} else if(SubW==5){
                drawsprite(WBmb, 13, 26, 11000);
        	} else if(SubW==6){
                drawsprite(WBib, 11, 26, 11000);
        	} else if(SubW==7){
                drawsprite(WBom, 13, 28, 11000);
            }
        }

        if(P2){
            int HP2 = getentityproperty(P2, "health");
            int MP2 = getentityproperty(P2, "mp");
            int SubW2 = getglobalvar("10");
            /*drawsprite(Bar, 3, 3, 1000);*/

            if(MP2>=100){
                MP2 = 99;
            }

            drawstring(-99,-99,4, MP2);
            /* drawbox(6,104-HP2,3,HP2,1500,rgbcolor(255,0,0),0);
            drawbox(8,104-HP2,1,HP2,1800,rgbcolor(255,104,104),0);
            drawbox(10,104-HP2,1,HP2,1500,rgbcolor(178,0,0),0); */

            if(SubW2==1){
                drawsprite(WKnif, 13, 145, 11000);
            } else if(SubW2==2){
                drawsprite(WAx, 13, 145, 11000);
            } else if(SubW2==3){
                drawsprite(WCrs, 13, 144, 11000);
            } else if(SubW2==4){
                drawsprite(WHoly, 13, 144, 11000);
            } else if(SubW2==5){
                drawsprite(WBmb, 13, 144, 11000);
            } else if(SubW2==6){
                drawsprite(WBib, 11, 144, 11000);
            } else if(SubW2==7){
                drawsprite(WBom, 13, 146, 11000);
            }
        }
    }
    if(openborvariant("in_menuscreen")==1){
      setglobalvar("00", NULL());
      setglobalvar("10", NULL());
    }
}

void oncreate()
{
    /*void Bar;*/
    void WAx; void WBib; void WBom; void WCrs; void WHoly; void WKnif; void WBmb;

    /*Bar = loadsprite("data/sprites/lifebar.gif");*/
    WAx = loadsprite("data/sprites/axe-icon-menu.gif");
    WBib = loadsprite("data/sprites/bible-icon-menu.gif");
    WBom = loadsprite("data/sprites/boomerang-icon-menu.gif");
    WCrs = loadsprite("data/sprites/cross-icon-menu.gif");
    WHoly = loadsprite("data/sprites/water-icon-menu.gif");
    WKnif = loadsprite("data/sprites/knife-icon-menu.gif");
    WBmb = loadsprite("data/sprites/bomb-icon-menu.gif");

    /*setglobalvar("Bar", Bar);*/
    setglobalvar("WAx", WAx);
    setglobalvar("WBib", WBib);
    setglobalvar("WBom", WBom);
    setglobalvar("WCrs", WCrs);
    setglobalvar("WHoly", WHoly);
    setglobalvar("WKnif", WKnif);
    setglobalvar("WBmb", WBmb);
}

void ondestroy(){
    /*void Bar = getglobalvar("Bar");*/
    void WAx = getglobalvar("WAx");
    void WBib = getglobalvar("WBib");
    void WBom = getglobalvar("WBom");
    void WCrs = getglobalvar("WCrs");
    void WHoly = getglobalvar("WHoly");
    void WKnif = getglobalvar("WKnif");
    void WBmb = getglobalvar("WBmb");

    /*free(Bar);*/
    free(WAx);
    free(WBib);
    free(WBom);
    free(WCrs);
    free(WHoly);
    free(WKnif);
    free(WBmb);

    /*setglobalvar("Bar", NULL());*/
    setglobalvar("WAx", NULL());
    setglobalvar("WBib", NULL());
    setglobalvar("WBom", NULL());
    setglobalvar("WCrs", NULL());
    setglobalvar("WHoly", NULL());
    setglobalvar("WKnif", NULL());
    setglobalvar("WBmb", NULL());
}