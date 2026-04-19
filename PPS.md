# Documentation PPS (Primary/Plan Position Symbol)

Ce document decrit les differentes representations PPS dessinees par le plugin.

Reference implementation:
- `CPPS::DrawPPS(...)` dans PPS.h
- appel de dessin depuis CSiTRadar.cpp

## 1. Parametres qui pilotent le symbole

Le rendu PPS depend principalement de:
- `radFlag` (niveau/type de source radar)
- `isCorrelated`
- `isVFR`
- `isADSB`
- `isRVSM`
- `squawk`
- `ppsColor`

## 2. Couleur PPS (logique generale)

Avant le dessin de forme, la couleur est calculee dans CSiTRadar:
- `radFlag == 0` -> jaune (`C_PPS_YELLOW`)
- `radFlag == 1` (cas principal non correle) -> magenta (`C_PPS_MAGENTA`)
- `squawk == 7600` ou `7700` -> rouge (`C_PPS_RED`)
- cible VFR correlee -> orange (`C_PPS_ORANGE`)
- sinon -> jaune

Override temporaire:
- si transpondeur ident (`TransponderI`) actif et tick clignotant -> blanc (`C_WHITE`)

## 3. Formes PPS par radFlag

## radFlag 0
- Aucun symbole specifique dessine dans DrawPPS (sortie sans trace).

## radFlag 1
- Correle: triangle (contour)
- Non correle: forme en Y

## radFlag 2 ou 3
Cas speciaux prioritaires:
- Squawk 7600/7700: triangle rempli
- Squawk 1200 non correle: triangle (contour)

Sinon:
- Correle IFR non-RVSM: hexagone radar (contour)
- Correle IFR RVSM: losange + barre verticale
- Correle VFR: cercle + marque interieure en V
- Non correle: croix combinee (X + +)

## radFlag 4
- Si `isADSB == false`: pas de dessin PPS en mode ADS-B pour ce flag
- Si `isADSB == true`:
  - Correle: carre
  - Correle + RVSM: carre + barre verticale
  - Non correle: carre + extensions externes (marques de non-correlation)

## radFlag 5, 6 ou 7
- Si `isADSB == true`:
  - Correle: carre
  - Correle + RVSM: carre + barre verticale
  - Non correle: carre + extensions externes
- Si `isADSB == false`:
  - Fallback vers la logique de symboles type 2/3
  - (hexagone/losange/cercle/croix selon correlation/VFR/RVSM)

## 4. Resume rapide (lecture operationnelle)

- ADS-B actif (`isADSB`): symbole carre (et barre RVSM si applicable)
- Non ADS-B:
  - correlation + IFR -> hexagone/losange
  - correlation + VFR -> cercle
  - non correlation -> croix/Y/triangle selon `radFlag` et squawk
- 7600/7700 force une representation d'urgence (triangle)

## 5. Notes de maintenance

- La forme est tracee dans PPS.h (fonction statique inline), pas dans PPS.cpp.
- La couleur est decidee en amont dans CSiTRadar, puis passee a DrawPPS.
- Les appels a DrawPPS sont faits dans les boucles de rendu radar IFR/VFR de CSiTRadar.

## 6. Schemas visuels (ASCII)

Ces schemas sont des representations simplifiees pour lecture rapide.

## radFlag 1

Correle (triangle):

```text
  /\
 /  \
/____\
```

Non correle (Y):

```text
\   /
 \ /
  |
  |
```

## radFlag 2/3

IFR correle non-RVSM (hexagone):

```text
  ____
 /    \
|      |
 \____/
```

IFR correle RVSM (losange + barre):

```text
   /\
  /  \
  \  /
   \/
   ||
```

VFR correle (cercle + V):

```text
  ____
 /    \
|  \/  |
 \____/
```

Non correle (X + +):

```text
\  |  /
 \ | /
-- + --
 / | \
/  |  \
```

Urgence 7600/7700 (triangle rempli):

```text
  /\
 /##\
/####\
```

## radFlag 4 (ADS-B)

ADS-B correle (carre):

```text
+----+
|    |
|    |
+----+
```

ADS-B correle RVSM (carre + barre):

```text
+----+
|  | |
|  | |
+----+
```

ADS-B non correle (carre + extensions):

```text
\ +----+ /
  |    |
--|    |--
  |    |
/ +----+ \
```

## radFlag 5/6/7

ADS-B actif: meme logique visuelle que radFlag 4.

Non ADS-B: fallback visuel vers les formes 2/3 (hexagone, losange RVSM, cercle VFR, croix non correle).

## Legende rapide

- Barre verticale interne: marqueur RVSM
- Carre: cible ADS-B
- Hexagone/losange/cercle: logique SSR/PSR non ADS-B
- Extensions externes: cible non correlee
