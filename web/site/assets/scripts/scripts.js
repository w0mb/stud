function sliderHandler() {
  // alert(1);
  console.log(4444);
  const slidesContainer = document.querySelector(".slider__overflow");
  const buttonsNextArray = document.querySelectorAll(".next");
  const buttonsPrevArray = document.querySelectorAll(".prev");

  let counter = 0;

  console.log(buttonsNextArray);
  buttonsNextArray.forEach((el, index) => {
    el.addEventListener("click", () => {
      if (counter !== 3) {
        counter++;

        slidesContainer.style.left = `-${counter}00%`;
      }
    });
  });
  buttonsPrevArray.forEach((el, index) => {
    el.addEventListener("click", () => {
      if (counter !== 0) {
        counter--;

        slidesContainer.style.left = `-${counter}00%`;
      }
    });
  });
}

function toggleWindow() {
  const messageWindow = document.querySelector(".modal__container");
  const buttons = document.querySelectorAll(".btn-modal");
  buttons.forEach((el) => {
    el.addEventListener("click", (e) => {
      messageWindow.classList.add("active");
    });
  });
  messageWindow.addEventListener("click", (e) => {
    if (e.target.classList.contains("modal__container")) {
      messageWindow.classList.remove("active");
    }
  });
}

function sendData() {
  const btn = document.querySelector(".modal__btn");
  const messageWindow = document.querySelector(".modal__container");

  const email = document.querySelector(".modal__email");
  const password = document.querySelector(".modal__password");
  const number = document.querySelector(".modal__number");
  const problems = [];
  function vaidate() {
    const EMAIL_REGEXP =
      /^(([^<>()[\].,;:\s@"]+(\.[^<>()[\].,;:\s@"]+)*)|(".+"))@(([^<>()[\].,;:\s@"]+\.)+[^<>()[\].,;:\s@"]{2,})$/iu;

    const NUMBER_REGEXP =
      /^(8|\+7)?[\s\-]?\(?[4-9]\d{2}\)?[\s\-]?\d{3}[\s\-]?\d{2}[\s\-]?\d{2}$/;
    if (!EMAIL_REGEXP.test(email.value)) problems.push("email");

    if (!NUMBER_REGEXP.test(number.value)) problems.push("number");

    if (password.value.length < 6) problems.push("password");
  }

  btn.addEventListener("click", () => {
    vaidate();
    if (problems.length === 0) {
      btn.classList.add("sending");
      fetch("https://jsonplaceholder.typicode.com/todos/1")
        .then((response) => response.json())
        .then((json) => {
          alert("Заявка отправлена");
          btn.classList.remove("sending");
          messageWindow.classList.remove("active");

          console.log(json);
        });
    } else {
      alert(`Ошибки в полях - ${problems.join(" , ")}`);
    }
    problems.length = 0;
  });
}

function modalPhoto() {
  const modal = document.querySelector(".modal-photo__window");
  const modalImg = modal.querySelector("img");
  const buttons = document.querySelectorAll("main img");
  buttons.forEach((el) => {
    el.addEventListener("click", (e) => {
      console.log(e.target);
      modalImg.src = e.target.src;
      modal.classList.add("active");
    });
  });

  modal.addEventListener("click", (e) => {
    console.log(3);
    if (e.target.classList.contains("modal-photo__window")) {
      modal.classList.remove("active");
    }
  });
}
modalPhoto();

toggleWindow();

sendData();

sliderHandler();

// Функция для плавной прокрутки
function smoothScroll(target) {
  document.querySelector(target).scrollIntoView({
    behavior: "smooth",
  });
}

// Функция для анимации появления элементов при прокрутке
function appearOnScroll() {
  const elements = document.querySelectorAll(".hidden");

  elements.forEach((element) => {
    // Проверка, виден ли элемент в текущем видимом окне
    const rect = element.getBoundingClientRect();
    const windowHeight =
      window.innerHeight || document.documentElement.clientHeight;
    const isVisible = rect.top <= windowHeight - 100;

    if (isVisible) {
      // Если элемент виден, добавляем класс 'fade-in'
      element.classList.add("fade-in");
    }
  });
}

// Плавная прокрутка для ссылок
document.querySelectorAll('a[href^="#"]').forEach((anchor) => {
  anchor.addEventListener("click", function (e) {
    e.preventDefault();
    smoothScroll(this.getAttribute("href"));
  });
});

// Слушатель событий для прокрутки
window.addEventListener("scroll", appearOnScroll);

// Вызов проверки видимости элементов при загрузке страницы
appearOnScroll();
