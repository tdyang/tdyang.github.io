// Smooth active nav highlighting on scroll
const sections = document.querySelectorAll('section[id]');
const navLinks = document.querySelectorAll('nav a[href*="#"]');

const observer = new IntersectionObserver((entries) => {
  entries.forEach(entry => {
    if (entry.isIntersecting) {
      navLinks.forEach(a => {
        a.classList.toggle('active', a.getAttribute('href').includes(entry.target.id));
      });
    }
  });
}, { threshold: 0.4 });

sections.forEach(s => observer.observe(s));
