# Tracy Yang — Portfolio

GitHub Pages portfolio site for Tracy Yang, Robotics Engineering BS '25 / MS '27 at WPI.

## Setup

1. Push this folder to a GitHub repo named `yourusername.github.io`
   (or any repo, then enable GitHub Pages in Settings → Pages → Deploy from branch → main)
2. Your site will be live at `https://yourusername.github.io`

## Structure

```
index.html          ← Home: hero, projects, skills, contact
coursework.html     ← All courses with descriptions + learning outcomes
css/style.css       ← All styles
js/main.js          ← Scroll-based nav highlight
_config.yml         ← GitHub Pages config (no Jekyll theme needed)
```

## Customizing

- **Email / GitHub / LinkedIn**: Update the three links in the `#contact` section of `index.html`
- **Project GitHub links**: Each Unified project card has a placeholder `href="#"` — replace with your actual repo URLs
- **Demo media**: Add `<img>` or `<video>` tags inside project cards to embed photos/GIFs of your robots
- **New projects**: Copy any `.project-card` block and fill in the details
