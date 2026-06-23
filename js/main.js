// Scroll fade-in
const fadeEls = document.querySelectorAll('.fade-in');
const fadeObserver = new IntersectionObserver((entries) => {
  entries.forEach((e, i) => {
    if (e.isIntersecting) {
      setTimeout(() => e.target.classList.add('visible'), i * 60);
      fadeObserver.unobserve(e.target);
    }
  });
}, { threshold: 0.12 });
fadeEls.forEach(el => fadeObserver.observe(el));
