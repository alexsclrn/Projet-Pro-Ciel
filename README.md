# PRO - Télécommande Arduino

Un site web pour contrôler tes projets Arduino via WiFi. La carte crée son propre réseau WiFi auquel tu peux te connecter directement sans avoir besoin d'Internet.

## Caractéristiques

- Interface web intuitive - contrôle depuis n'importe quel navigateur
- Réseau WiFi autonome - crée son propre SSID
- Communication en temps réel
- Compatible mobile et ordinateur
- Facile à configurer

## Installation rapide

### Prérequis

- Une carte Arduino compatible WiFi (ESP8266, ESP32, etc.)
- Un navigateur web moderne

### Setup

1. Clone le repo
   ```bash
   git clone https://github.com/alexsclrn/PRO.git
   cd PRO
   ```

2. Charge le code Arduino
   - Ouvre l'Arduino IDE
   - Upload le sketch Arduino sur ta carte
   - Configure les paramètres WiFi (SSID et mot de passe)

3. Connecte-toi
   - Connecte-toi au réseau WiFi créé par ton Arduino
   - Ouvre ton navigateur et va à `http://192.168.4.1`
   - Prêt à contrôler !

## Configuration

### WiFi

```cpp
const char* ssid = "PRO";           // Nom du réseau
const char* password = "password";   // Mot de passe
```

## Structure du projet

```
PRO/
├── README.md
├── arduino/
│   └── sketch.ino
├── web/
│   ├── index.html
│   ├── style.css
│   └── script.js
└── docs/
```

## Utilisation

1. Allume ton Arduino
2. Attends que le réseau WiFi apparaisse
3. Connecte-toi
4. Accède à l'interface web
5. Contrôle tes appareils

## Contribuer

Des bugs? Des idées? Ouvre une issue ou envoie une PR.

## Licence

À définir

## Questions?

Ouvre une issue sur le repo.