ReplacementTable={
      [":lemon:"] = "🍋",
      [":hibiscus:"] = "🌺",
      [":peanuts:"] = "🥜",
      [":snow_capped_mountain:"] = " 🏔 ",
      [":beach:"] = " 🏖 ",
      [":national_park:"] = " 🏞 ",
      [":money_bag:"] = " 💰 ",
      [":see_no_evil_monkey:"] = " 🙈 ",
      [":hear_no_evil_monkey:"] = " 🙉 ",
      [":speak_no_evil_monkey:"] = " 🙊 "}

function Str (s)
  return pandoc.Str(s.text:gsub("%S+", ReplacementTable))
end
