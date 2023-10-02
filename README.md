# breakout
Final Task - Breakout

### Gruppe: Torben und Justus

Kompilieren : make
Starten : ./breakout

Steuerung : Rechts und Links mit Pfeiltasten, Leertaste schiesst den ersten Ball,
            q beendet das Spiel, r startet das Spiel neu, b um die automatische Steuerung zu aktivieren

Spezielle Steine : Normaler Stein$, Stein der zweimal getroffen werden muss2, Stein der weiteren Ball hinzufügt0

Falls der Ball hinter einem Stein verschwindet sieht dass nur so aus, dass Model simuliert alle Bewegungen deutlich genauer als es der View darstellen kann.

Das Spiel ist gewonnen wenn alle Steine kaputt sind

Das Spiel ist verloren wenn kein Ball mehr im Spiel ist


Überarbeitung:

Wir haben jetzt 3 funktionierende (und natürlich sinnvolle) Tests hinzugefügt
Den Makefile haben wir auch geupdatet

Ausführung der Tests:

1. make tests
2. ./tests